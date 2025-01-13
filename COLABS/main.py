import os
from torch.utils.data import DataLoader
import torch.optim as optim
from function import *

# Check if GPU is available
print("Checking for GPU availability...")
device = get_gpu_device()

# # Downloading and extracting the dataset
# print("Checking for dataset...")
# if not os.path.exists('data'):
#     print("Downloading and extracting the dataset...")
#     download_and_extract_tar_gz_dataset_from_gdrive()

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


exit = True
while exit:
# Loading or Training the model
    user_model = 't'
    while True:  # Loop to get valid input
        user_model = input("Do you want to load (l) or train (t) a model? (l/t): ").strip().lower()
        if user_model == 'l' or user_model == 't':
            break
        else:
            print("Invalid input. Please enter 'l' or 't'.")
            
    if user_model == 'l':
        # Loading Model
        model = load_model(model, device)
    elif user_model == 't':
        pos_weight = torch.tensor([3.0], device=device)  # Adjust based on class imbalance
        optimizer = optim.Adam(model.parameters(), lr=0.001)
        criterion = nn.CrossEntropyLoss()  # Updated loss function (nn.BCEWithLogitsLoss(pos_weight=pos_weight) / nn.BCELoss(weight=weights))
        # Training the model
        train_model(model=model, 
                    optimizer=optimizer, 
                    criterion=criterion, 
                    train_loader=train_loader, 
                    device=device, 
                    num_epochs=10)
# Saving the model
        while True:  # Loop to get valid input
            user_save = input("Do you want to save model ? (y/n): ").strip().lower()
            if user_save == 'y':
                # Save the model
                save_model(model)
                break
            elif user_save == 'n':
                print(f"Continuing without saving the model...")
                break
            else:
                print("Invalid input. Please enter 'y' or 'n'.")
        

# Testing the model
    while True:  # Loop to get valid input
        user_test = input("Wich test do you want to do: \n all (0) \n predict image (1) \n display tumor highlight (2) \n confusion_matrix (3) \n test model (4) \n visualize predictions (5) \n quit (6)? \n (0/1/2/3/4/5/6): ").strip().lower()
        if user_test == '0':
            # Predict and print the result
            predict_image(model, device, input("Enter the image file path: "), transform)
            # Display the tumor highlight
            display_tumor_highlight(model, device, input("Enter the image file path: "), transform)
            # Assuming your model and test_loader are already defined and device is set
            test_model_with_confusion_matrix(model, test_loader, device, threshold=0.5)
            # Testing the model
            test_model(model=model, 
                    test_loader=test_loader, 
                    device=device)
            # Visualizing some predictions
            visualize_predictions(model=model, 
                                test_loader=test_loader, 
                                device=device, 
                                num_images=5)
        elif user_test == '1':
            # Predict and print the result
            predict_image(model, device, input("Enter the image file path: "), transform)
        elif user_test == '2':
            # Display the tumor highlight
            display_tumor_highlight(model, device, input("Enter the image file path: "), transform)
        elif user_test == '3':
            # Assuming your model and test_loader are already defined and device is set
            test_model_with_confusion_matrix(model, test_loader, device, threshold=0.5)
        elif user_test == '4':
            # Testing the model
            test_model(model=model, 
                    test_loader=test_loader, 
                    device=device)
        elif user_test == '5':
            # Visualizing some predictions
            visualize_predictions(model=model, 
                                test_loader=test_loader, 
                                device=device, 
                                num_images=5)
        elif user_test == '6':
            break
        else:
            print("Invalid input. Please enter valide input.")

# Exit the program
    while True:  # Loop to get valid input
        user_input = input("Do you want to exit ? (y/n): ").strip().lower()
        if user_input == 'y':
            exit = False
            print("Exiting...")
            break
        elif user_input == 'n':
            print("Continuing...")
            break
        else:
            print("Invalid input. Please enter 'y' or 'n'.")