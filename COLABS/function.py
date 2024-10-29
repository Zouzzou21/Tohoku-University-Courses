import os, tarfile, gdown, torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset
from torchvision import transforms
from PIL import Image
from sklearn.metrics import accuracy_score, precision_score, recall_score
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
    print(f'Model name: |{model_name}|')
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
        x = torch.sigmoid(self.fc2(x))
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
def evaluate_model(model, test_loader, device):
    print("Evaluating model...")
    model.eval()
    all_preds, all_labels = [], []
    with torch.no_grad():
        for images, labels in test_loader:
            images, labels = images.to(device), labels.to(device)
            # print(f"Predictions: {all_preds[:10]}, Labels: {all_labels[:10]}")
            outputs = model(images)
            preds = torch.round(outputs).squeeze()
            all_preds.extend(preds.cpu().numpy())
            all_labels.extend(labels.cpu().numpy())
    accuracy = accuracy_score(all_labels, all_preds)
    precision = precision_score(all_labels, all_preds)
    recall = recall_score(all_labels, all_preds)
    print(f'Accuracy: {accuracy}, Precision: {precision}, Recall: {recall}')
    print("Evaluation completed.")

# Function to test the model on the test dataset and calculate accuracy
def test_model(model, test_loader, device):
    print("Testing model...")
    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for images, labels in test_loader:
            images, labels = images.to(device), labels.to(device)
            outputs = model(images)
            preds = torch.round(outputs).squeeze()
            total += labels.size(0)
            correct += (preds == labels).sum().item() 
    print(f'Test Accuracy: {correct / total * 100:.2f}%')
    print(f'Correct prediction: {correct} out of a total of {total}')
    print("Testing completed.")

# Visualizing predictions
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
                image = images[i].permute(1, 2, 0).cpu().numpy()
                original_image = test_loader.dataset.dataset.images[test_loader.dataset.indices[i]]
                original_image = Image.open(original_image).convert('RGB')
                label = labels[i].item()
                pred = preds[i].item()
                # Display original image
                plt.subplot(1, 2, 1)
                plt.imshow(original_image)
                plt.title(f"Original: {'Tumor' if label == 1 else 'No Tumor'}")
                # Display transformed image
                plt.subplot(1, 2, 2)
                plt.imshow(image)
                plt.title(f"Prediction: {'Tumor' if pred == 1 else 'No Tumor'}")
                plt.show()
                images_shown += 1
    print("Visualization completed.")