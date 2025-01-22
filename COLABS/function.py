import os, torch, cv2 #, tarfile, gdown
from datetime import datetime
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
from torch.utils.data import Dataset
from PIL import Image
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt
import numpy as np

# # Downloading the dataset
# def download_and_extract_tar_gz_dataset_from_gdrive(file_id='16HXjRo49A4WYkaai-vXkIFLnjsDAA4EE', extract_to='data'):
#     """Downloads a .tar.gz file from Google Drive, extracts it, and deletes the original .tar.gz file."""
#     url = f"https://drive.google.com/uc?id={file_id}"
#     output = "data.tar.gz"
#     print("Starting download...")
#     gdown.download(url, output, quiet=False)
#     print(f"Extracting {output} to {extract_to}...")
#     with tarfile.open(output, "r:gz") as tar:
#         tar.extractall(path=extract_to)
#     os.remove(output) if os.path.exists(output) else print(f"{output} not found.")

# Display available GPUs
def get_gpu_device():
    if torch.cuda.is_available():
        gpu_count = torch.cuda.device_count()
        for i in range(gpu_count):
            device_properties = torch.cuda.get_device_properties(i)
            total_memory = device_properties.total_memory / 1024**3  # Convert from bytes to GB
            print(f"GPU {i}: {torch.cuda.get_device_name(i)}")
            print(f"Total Memory: {total_memory:.2f} GB")
            print(f"Memory Allocated: {torch.cuda.memory_allocated(i) / 1024**3:.2f} GB")
            print(f"Memory Cached: {torch.cuda.memory_reserved(i) / 1024**3:.2f} GB")
            print(f"CUDA Capability: {torch.cuda.get_device_capability(i)}\n")
        return torch.device(f"cuda")
    else:
        print("No GPU available.")
        return torch.device("cpu")

# Saving the model
def save_model(model):
    model_name = input("Enter the path for the saved model (with .pth extension): ")
    if not model_name.endswith('.pth'):
        model_name += '.pth'
    torch.save(model.state_dict(), model_name)
    print(f"Model {model_name} saved!")

# Load the model on the appropriate device
def load_model(model, device):
    model_name = input("Enter the path for the model to load (with .pth extension): ")
    if model_name == "":
        print("No model provided. Using default model.")
        model_name = 'model/model.pth'
    else:
        if not model_name.endswith('.pth'):
            model_name += '.pth'
    # device = get_gpu_device()  # Get the appropriate device (CUDA or CPU)
    state_dict = torch.load(model_name, map_location=device, weights_only=True)
    model.load_state_dict(state_dict)
    model.to(device)  # Move the model to the device
    model.eval()
    print(f"Model {model_name} loaded on {device}!")
    return model

# Custom dataset to load MRI images
class TumorDataset(Dataset):
    def __init__(self, image_dir = 'data/', transform=None):
        self.image_dir = image_dir
        self.transform = transform
        self.images, self.labels = [], []
        for label, folder in enumerate(['notumor', 'glioma', 'meningioma', 'pituitary']):
            folder_path = os.path.join(image_dir, folder)
            for img_name in os.listdir(folder_path):
                img_path = os.path.join(folder_path, img_name)
                self.images.append(img_path)
                self.labels.append(label)
    def __len__(self):
        return len(self.images)
    def __getitem__(self, idx):
        image = Image.open(self.images[idx]).convert('RGB')
        if self.transform:
            image = self.transform(image)
        label = torch.tensor(self.labels[idx], dtype=torch.float32)
        return image, label

# CNN Model
class TumorDetectionCNN(nn.Module):
    def __init__(self):
        super(TumorDetectionCNN, self).__init__()
        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, stride=1, padding=1)
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1)
        self.pool = nn.MaxPool2d(2, 2)
        self.fc1 = nn.Linear(64 * 56 * 56, 512)
        self.fc2 = nn.Linear(512, 4)  # Updated for 4 output classes
    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 64 * 56 * 56)
        x = F.relu(self.fc1(x))
        x = self.fc2(x)  # 4 outputs for each class
        return x

# Training function
def train_model(model, optimizer, criterion, train_loader, device, num_epochs=5):
    print(f'{datetime.now().time()} - Starting training...')
    model.train()
    for epoch in range(num_epochs):
        running_loss = 0.0
        for images, labels in train_loader:
            images, labels = images.to(device), labels.to(device)
            labels = labels.long()
            # Zero the parameter gradients
            optimizer.zero_grad()
            # Forward pass
            outputs = model(images)
            loss = criterion(outputs, labels)  # Compute loss
            loss.backward()  # Backpropagation
            optimizer.step()  # Update weights
            # Accumulate loss
            running_loss += loss.item()
        print(f'{datetime.now().time()} - Epoch {epoch+1}/{num_epochs}, Loss: {running_loss/len(train_loader)}')
    print("Training completed.")

# Function to evaluate the model on the test dataset
def test_model(model, test_loader, device):
    print("Testing model with four tumor classes...")
    model.eval()  # Set model to evaluation mode
    total = 0
    correct = 0
    # Initialize counters for errors per class
    class_errors = {0: 0, 1: 0, 2: 0, 3: 0}  # One counter for each class
    class_totals = {0: 0, 1: 0, 2: 0, 3: 0}
    class_names = ['No Tumor', 'Glioma', 'Meningioma', 'Pituitary']
    with torch.no_grad():  # Disable gradient tracking for testing
        for images, labels in test_loader:
            # Move images and labels to the appropriate device (GPU/CPU)
            images, labels = images.to(device), labels.to(device)
            # Get model outputs and compute predictions
            outputs = model(images)
            _, preds = torch.max(outputs, 1)  # Get the class with the highest score
            # Accumulate total and correct predictions
            total += labels.size(0)
            correct += (preds == labels).sum().item()
            # Track errors per class
            for i in range(labels.size(0)):
                true_label = int(labels[i].item())
                pred_label = int(preds[i].item())
                # Increment class-specific totals
                class_totals[true_label] += 1
                # Increment errors if prediction is wrong
                if true_label != pred_label:
                    class_errors[true_label] += 1
    # Calculate overall accuracy
    accuracy = correct / total * 100
    print(f'Test Accuracy: {accuracy:.2f}%')
    print(f'Correct predictions: {correct} out of {total}')
    # Display errors for each class
    for class_label, total_count in class_totals.items():
        error_count = class_errors[class_label]
        error_rate = error_count / total_count * 100 if total_count > 0 else 0
        print(f"Class '{class_names[class_label]}' - Total: {total_count}, Errors: {error_count}, Error Rate: {error_rate:.2f}%")
    print("Testing completed.")

# # Function to test the model and display confusion matrix
def test_model_with_confusion_matrix(model, test_loader, device, threshold=0.5):
    print("Testing model and analyzing errors with confusion matrix...")
    model.eval()  # Set model to evaluation mode
    all_preds = []
    all_labels = []
    with torch.no_grad():  # Disable gradient tracking for testing
        for images, labels in test_loader:
            images = images.to(device)
            labels = labels.to(device)
            # Get model outputs and compute predictions
            outputs = model(images)
            # Convert outputs to class predictions
            preds = torch.argmax(outputs, dim=1)  # Get class labels (0, 1, 2, or 3)
            # Collect all predictions and true labels
            all_preds.extend(preds.cpu().numpy())  # Convert to numpy and add to list
            all_labels.extend(labels.cpu().numpy())  # Ensure true labels are class labels as well
    # Compute confusion matrix
    cm = confusion_matrix(all_labels, all_preds)
    # Display confusion matrix
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=['No Tumor', 'Tumor Type 1', 'Tumor Type 2', 'Tumor Type 3'])
    disp.plot(cmap='Blues')
    plt.title('Confusion Matrix')
    plt.show()
    print("Confusion matrix displayed.")


# Function to visualize predictions
def visualize_predictions(model, test_loader, device, num_images=5):
    print("Visualizing predictions...")
    model.eval()
    images_shown = 0
    
    # Define the class names for each label
    class_names = ['No Tumor', 'Glioma', 'Meningioma', 'Pituitary']
    
    with torch.no_grad():
        for images, labels in test_loader:
            images, labels = images.to(device), labels.to(device)
            labels = labels.long()  # Ensure labels are integers
            outputs = model(images)
            preds = torch.argmax(outputs, dim=1)  # Get the predicted class labels
            
            for i in range(len(images)):
                if images_shown >= num_images:
                    return
                
                # Ensure correct range for displaying (0-1 or 0-255)
                image = images[i].cpu().numpy().transpose(1, 2, 0)
                image = (image - image.min()) / (image.max() - image.min())  # Normalize to [0, 1]
                
                # Get true and predicted labels as descriptive names
                true_label_name = class_names[labels[i].item()]
                pred_label_name = class_names[preds[i].item()]
                
                # Display the image and prediction information
                plt.figure(figsize=(6, 3))
                
                # Display transformed image
                plt.subplot(1, 2, 1)
                plt.imshow(image)
                plt.title(f"True: {true_label_name}")
                plt.axis('off')
                
                # Display prediction label
                plt.subplot(1, 2, 2)
                plt.imshow(image)
                plt.title(f"Prediction: {pred_label_name}")
                plt.axis('off')
                
                plt.show()
                
                images_shown += 1

    print("Visualization completed.")

# Function to preprocess the image
def preprocess_image(image_path, transform):
    transform = transforms.Compose([
        transforms.Resize((224, 224)),  # Same size as training images
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])  # Same normalization as training
    ])
    image = Image.open(image_path).convert('RGB')  # Ensure it's in RGB mode
    image = transform(image).unsqueeze(0)  # Add batch dimension
    return image

# Function to make a prediction with the trained model
def predict_image(model, device, image_path, transform):
    # Display the image
    img = Image.open(image_path)
    plt.imshow(img)
    plt.axis('off')
    plt.title("Uploaded Image")
    plt.show()
    model.eval()  # Set model to evaluation mode
    image = preprocess_image(image_path, transform).to(device)
    with torch.no_grad():  # Disable gradient tracking
        output = model(image)
        pred_class = torch.argmax(output).item()  # Get the class with the highest score
    # Define class names to interpret the prediction
    class_names = ['No Tumor', 'Glioma', 'Meningioma', 'Pituitary']
    print(f"Prediction: {class_names[pred_class]}")


def display_tumor_highlight(model, device, image_path, transform):
    model.to(device)  # Ensure model is on GPU
    model.eval()  # Set model to evaluation mode
    # Preprocess the image and move to the correct device
    image = preprocess_image(image_path, transform).to(device)
    image.requires_grad = True  # Enable gradients for the image
    # Forward pass to get the model output
    output = model(image)
    pred_class = torch.argmax(output).item()  # Get the class with the highest score
    # Check if a tumor is detected
    class_names = ['No Tumor', 'Glioma', 'Meningioma', 'Pituitary']
    if pred_class == 0:
        print("No tumor detected in the image.")
        plt.imshow(Image.open(image_path))
        plt.axis('off')
        plt.title("No Tumor Detected")
        plt.show()
        return
    # Identify the last convolutional layer for Grad-CAM
    def get_last_conv_layer(model):
        modules = list(model.named_modules())
        for name, layer in reversed(modules):
            if isinstance(layer, nn.Conv2d):
                return layer
        raise ValueError("No convolutional layer found in the model.")
    last_conv_layer = get_last_conv_layer(model)
    # Run a forward pass and capture the activations
    activations = None
    def forward_hook(module, input, output):
        nonlocal activations
        activations = output  # Capture the output (activations) of the last conv layer
    # Register the forward hook on the last convolutional layer
    hook = last_conv_layer.register_forward_hook(forward_hook)
    # Perform the forward pass again to trigger the hook and capture activations
    output = model(image)
    target = output[0, pred_class]  # Get output for the target class
    # Remove the forward hook
    hook.remove()
    # Check if activations were captured
    if activations is None:
        raise RuntimeError("Failed to capture activations for the last convolutional layer.")
    # Register a hook on the activations to capture gradients during backpropagation
    gradients = []
    def backward_hook(grad):
        gradients.append(grad)
    # Attach the backward hook to the activations
    activations.register_hook(backward_hook)
    # Zero out any existing gradients and perform backpropagation
    model.zero_grad()
    target.backward()
    # Ensure gradients were captured
    if not gradients:
        raise RuntimeError("Failed to capture gradients for the last convolutional layer.")
    # Process captured gradients and activations for Grad-CAM
    gradient = gradients[0].squeeze().cpu().data.numpy()  # Shape [C, H, W]
    activation = activations.squeeze().cpu().data.numpy()  # Shape [C, H, W]
    # Compute weights for each channel
    weights = np.mean(gradient, axis=(1, 2))
    # Create Grad-CAM heatmap
    grad_cam = np.zeros(activation.shape[1:], dtype=np.float32)
    for i, w in enumerate(weights):
        grad_cam += w * activation[i]
    # ReLU to remove negative values and normalize
    grad_cam = np.maximum(grad_cam, 0)
    grad_cam = (grad_cam - grad_cam.min()) / (grad_cam.max() - grad_cam.min() + 1e-5)  # Normalize to [0, 1]
    # Load original image and ensure it's resized to the same size as the heatmap
    img = cv2.cvtColor(np.array(Image.open(image_path).resize((224, 224))), cv2.COLOR_RGB2BGR)
    # Resize grad_cam to match the image dimensions
    heatmap = cv2.applyColorMap(np.uint8(255 * cv2.resize(grad_cam, (224, 224))), cv2.COLORMAP_JET)
    # Overlay Grad-CAM heatmap on the original image
    overlay = cv2.addWeighted(img, 0.5, heatmap, 0.5, 0)
    # Display the image with Grad-CAM heatmap
    plt.figure(figsize=(8, 8))
    plt.imshow(cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB))
    plt.axis('off')
    plt.title(f"Tumor Detected: {class_names[pred_class]}")
    plt.show()