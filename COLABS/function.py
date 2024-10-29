import os, tarfile, gdown, torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
from torch.utils.data import Dataset
from PIL import Image
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

# Downloading the dataset
def download_and_extract_tar_gz_dataset_from_gdrive(file_id='11Sm64svCR4nhI7fBBPuYT43JwVJoC-Ev', extract_to='data'):
    """Downloads a .tar.gz file from Google Drive, extracts it, and deletes the original .tar.gz file."""
    url = f"https://drive.google.com/uc?id={file_id}"
    output = "data.tar.gz"
    print("Starting download...")
    gdown.download(url, output, quiet=False)
    print(f"Extracting {output} to {extract_to}...")
    with tarfile.open(output, "r:gz") as tar:
        tar.extractall(path=extract_to)
    os.remove(output) if os.path.exists(output) else print(f"{output} not found.")

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
    print("Model {model_name} saved!")

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
        for label, folder in enumerate(['no_tumor', 'tumor']):
            folder_path = os.path.join(image_dir, folder)
            for img_name in os.listdir(folder_path):
                img_path = os.path.join(folder_path, img_name)
                self.images.append(img_path)
                self.labels.append(label)  # 0 for no_tumor, 1 for tumor
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
        self.fc2 = nn.Linear(512, 1)
    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 64 * 56 * 56)
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        # x = torch.sigmoid(self.fc2(x))
        return x

# Training function
def train_model(model, optimizer, criterion, train_loader, device, num_epochs=5):
    # num_epochs = input("Enter the number of epochs: ")
    print("Starting training...")
    model.train()
    for epoch in range(num_epochs):
        running_loss = 0.0
        for images, labels in train_loader:
            images, labels = images.to(device), labels.to(device)
            labels = labels.float().unsqueeze(1)  # Adjusting the size of the labels
            optimizer.zero_grad()
            outputs = model(images)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            running_loss += loss.item()
        print(f'Epoch {epoch+1}/{num_epochs}, Loss: {running_loss/len(train_loader)}')
    print("Training completed.")

# Evaluation function
# def evaluate_model(model, test_loader, device):
#     print("Evaluating model...")
#     model.eval()
#     all_preds, all_labels = [], []
#     with torch.no_grad():
#         for images, labels in test_loader:
#             images, labels = images.to(device), labels.to(device)
#             # print(f"Predictions: {all_preds[:10]}, Labels: {all_labels[:10]}")
#             outputs = model(images)
#             preds = torch.round(outputs).squeeze()
#             all_preds.extend(preds.cpu().numpy())
#             all_labels.extend(labels.cpu().numpy())
#     accuracy = accuracy_score(all_labels, all_preds)
#     precision = precision_score(all_labels, all_preds)
#     recall = recall_score(all_labels, all_preds)
#     print(f'Accuracy: {accuracy}, Precision: {precision}, Recall: {recall}')
#     print("Evaluation completed.")

# Function to test the model on the test dataset and calculate accuracy
def test_model(model, test_loader, device):
# Enhanced test_model function to identify class-specific errors
    print("Testing model...")
    model.eval()  # Set model to evaluation mode
    total = 0
    correct = 0
    # Initialize counters for errors per class
    class_errors = {'no_tumor': 0, 'tumor': 0}
    class_totals = {'no_tumor': 0, 'tumor': 0}
    with torch.no_grad():  # Disable gradient tracking for testing
        for images, labels in test_loader:
            # Move images and labels to the appropriate device (GPU/CPU)
            images, labels = images.to(device), labels.to(device)
            # Get model outputs and compute predictions
            outputs = model(images).squeeze()
            probs = torch.sigmoid(outputs)  # Get probabilities
            preds = torch.round(probs)  # Round probabilities to 0 or 1
            # Accumulate total and correct predictions
            total += labels.size(0)
            correct += (preds == labels).sum().item()
            # Track errors per class
            for i in range(labels.size(0)):
                true_label = int(labels[i].item())
                pred_label = int(preds[i].item())
                # Increment class-specific totals
                if true_label == 0:
                    class_totals['no_tumor'] += 1
                else:
                    class_totals['tumor'] += 1
                # Increment errors if prediction is wrong
                if true_label != pred_label:
                    if true_label == 0:
                        class_errors['no_tumor'] += 1
                    else:
                        class_errors['tumor'] += 1
    # Calculate overall accuracy
    accuracy = correct / total * 100
    # Display overall accuracy and class-specific error rates
    print(f'Test Accuracy: {accuracy:.2f}%')
    print(f'Correct predictions: {correct} out of {total}')
    # Display errors for each class
    for class_name, total_count in class_totals.items():
        error_count = class_errors[class_name]
        error_rate = error_count / total_count * 100 if total_count > 0 else 0
        print(f"Class '{class_name}' - Total: {total_count}, Errors: {error_count}, Error Rate: {error_rate:.2f}%")
    print("Testing completed.")

# Function to test the model and display confusion matrix
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
            outputs = model(images).squeeze()
            probs = torch.sigmoid(outputs)  # Apply sigmoid for probability scores
            preds = (probs >= threshold).float()  # Apply threshold to get binary predictions
            # Collect all predictions and true labels
            all_preds.extend(preds.cpu().numpy())
            all_labels.extend(labels.cpu().numpy())
    # Compute confusion matrix
    cm = confusion_matrix(all_labels, all_preds)
    # Display confusion matrix
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=['No Tumor', 'Tumor'])
    disp.plot(cmap='Blues')
    plt.title('Confusion Matrix')
    plt.show()
    print("Confusion matrix displayed.")


def visualize_predictions(model, test_loader, device, num_images=5):
    print("Visualizing predictions...")
    model.eval()
    images_shown = 0
    with torch.no_grad():
        for images, labels in test_loader:
            images, labels = images.to(device), labels.to(device)
            outputs = model(images).squeeze()
            preds = torch.round(outputs)
            for i in range(len(images)):
                if images_shown >= num_images:
                    return
                # Ensure correct range for displaying (0-1 or 0-255)
                image = images[i].cpu().numpy().transpose(1, 2, 0)
                image = (image - image.min()) / (image.max() - image.min())  # Normalize to [0, 1]
                # Load original image from path for comparison
                original_image_path = test_loader.dataset.dataset.images[test_loader.dataset.indices[i]]
                original_image = Image.open(original_image_path).convert('RGB')
                label = labels[i].item()
                pred = preds[i].item()
                # Display original image
                plt.subplot(1, 2, 1)
                plt.imshow(original_image)
                plt.title(f"Original: {'Tumor' if label == 1 else 'No Tumor'}")
                plt.axis('off')
                # Display prediction image with normalization fix
                plt.subplot(1, 2, 2)
                plt.imshow(image)
                plt.title(f"Prediction: {'Tumor' if pred == 1 else 'No Tumor'}")
                plt.axis('off')
                plt.show()
                images_shown += 1
    print("Visualization completed.")

# Visualizing predictions
# def visualize_predictions(model, test_loader, device, num_images=5):
#     print("Visualizing predictions...")
#     model.eval()
#     images_shown = 0
#     with torch.no_grad():
#         for images, labels in test_loader:
#             images, labels = images.to(device), labels.to(device)
#             outputs = model(images).squeeze()
#             preds = torch.round(outputs)
#             for i in range(len(images)):
#                 if images_shown >= num_images:
#                     return
#                 image = images[i].permute(1, 2, 0).cpu().numpy()
#                 original_image = test_loader.dataset.dataset.images[test_loader.dataset.indices[i]]
#                 original_image = Image.open(original_image).convert('RGB')
#                 label = labels[i].item()
#                 pred = preds[i].item()
#                 # Display original image
#                 plt.subplot(1, 2, 1)
#                 plt.imshow(original_image)
#                 plt.title(f"Original: {'Tumor' if label == 1 else 'No Tumor'}")
#                 # Display transformed image
#                 plt.subplot(1, 2, 2)
#                 plt.imshow(image)
#                 plt.title(f"Prediction: {'Tumor' if pred == 1 else 'No Tumor'}")
#                 plt.show()
#                 images_shown += 1
#     print("Visualization completed.")

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
        output = model(image).squeeze()
        prob = torch.sigmoid(output).item()  # Get probability score
    # Return prediction based on probability
    if prob >= 0.5:
        print(f"Prediction: Tumor (Confidence: {prob:.2f})")
    else:
        print(f"Prediction: No Tumor (Confidence: {1 - prob:.2f})")