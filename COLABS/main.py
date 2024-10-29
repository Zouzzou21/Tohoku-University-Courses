import os
from torch.utils.data import DataLoader
import torch.optim as optim
from function import *

# Check if GPU is available
print("Checking for GPU availability...")
device = get_gpu_device()

# Downloading and extracting the dataset
print("Checking for dataset...")
if not os.path.exists('data'):
    print("Downloading and extracting the dataset...")
    download_and_extract_tar_gz_dataset_from_gdrive()

# Image transformations
print("Applying image transformations...")
transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
])

# Loading data
print("Loading dataset...")
dataset = TumorDataset(transform=transform)

# Train/test split
print("Splitting dataset into train and test sets...")
train_size = int(0.8 * len(dataset))
test_size = len(dataset) - train_size
train_dataset, test_dataset = torch.utils.data.random_split(dataset, [train_size, test_size])

# Dataloaders
print("Creating dataloaders...")
train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False)

# Initializing the model, loss function, and optimizer
print("Initializing model, loss function, and optimizer...")
model = TumorDetectionCNN().to(device)
model = load_model(model, device)
pos_weight = torch.tensor([3.0], device=device)  # Adjust based on class imbalance
criterion = nn.BCEWithLogitsLoss(pos_weight=pos_weight)
# criterion = nn.BCELoss(weight=weights)
optimizer = optim.Adam(model.parameters(), lr=0.001)

# Training the model
# train_model(model=model, 
#             optimizer=optimizer, 
#             criterion=criterion, 
#             train_loader=train_loader, 
#             device=device, 
#             num_epochs=10)

# Save the model
# save_model(model)

# Evaluating the model
# evaluate_model(model=model, 
#                test_loader=test_loader, 
#                device=device)


# Predict and print the result
predict_image(model, device, input("Enter the image file path: "), transform)



# Assuming your model and test_loader are already defined and device is set
# test_model_with_confusion_matrix(model, test_loader, device, threshold=0.5)


# # Testing the model
# test_model(model=model, 
#            test_loader=test_loader, 
#            device=device)

# # Visualizing some predictions
# visualize_predictions(model=model, 
#                       test_loader=test_loader, 
#                       device=device, 
#                       num_images=5)