import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import models, transforms
from torch.utils.data import DataLoader
from function import TumorDataset, train_model, test_model_with_confusion_matrix, test_model

# Check for GPU availability
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Device: {device}")

# Function to load ResNet-18
def load_resnet18(num_classes):
    model = models.resnet18(pretrained=True)
    model.fc = nn.Linear(model.fc.in_features, num_classes)
    return model

# Function to load MobileNet-V2
def load_mobilenet_v2(num_classes):
    model = models.mobilenet_v2(pretrained=True)
    model.classifier[1] = nn.Linear(model.last_channel, num_classes)
    return model

# Function to test a model
def test_model_pipeline(model_name, model, train_loader, test_loader, device):
    print(f"\n--- Testing {model_name} ---")
    
    # Initialize optimizer and loss function
    optimizer = optim.Adam(model.parameters(), lr=0.001)
    criterion = nn.CrossEntropyLoss()

    # Train the model
    print(f"Training {model_name}...")
    train_model(
        model=model,
        optimizer=optimizer,
        criterion=criterion,
        train_loader=train_loader,
        device=device,
        num_epochs=100  # You can change this value
    )
    
    # Test the model with confusion matrix
    print(f"Evaluating {model_name}...")
    test_model_with_confusion_matrix(model, test_loader, device)

    # Test overall metrics
    test_model(model, test_loader, device)

# Load the dataset
print("Loading the dataset...")
transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
])
dataset = TumorDataset(transform=transform)

# Split dataset into training and testing sets
train_size = int(0.8 * len(dataset))
test_size = len(dataset) - train_size
train_dataset, test_dataset = torch.utils.data.random_split(dataset, [train_size, test_size])
train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False)

# Choose the model to test
models_to_test = {
    "ResNet-18": load_resnet18(num_classes=4),
    "MobileNet-V2": load_mobilenet_v2(num_classes=4)
}

# Test each model
for model_name, model in models_to_test.items():
    model = model.to(device)  # Move model to GPU/CPU
    test_model_pipeline(model_name, model, train_loader, test_loader, device)

print("All models have been tested.")
