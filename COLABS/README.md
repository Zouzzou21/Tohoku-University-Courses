# How to execute this program?

## 1. Dataset:
Download and extract the dataset to the following location: ```Tohoku-University-Courses/COLABS/data/```
This program is designed to work with four classes of tumors. Please organize your dataset as follows:
```
data/
├───glioma/
├───meningioma/
├───notumor/
└───pituitary/
```
For testing, the [Brain Tumor MRI Dataset - Masoud Nickparvar](https://www.kaggle.com/datasets/masoudnickparvar/brain-tumor-mri-dataset) from Kaggle is recommended.

I also put an archive on my Google Drive: https://drive.google.com/file/d/16mQqDbM73ljmPcJYmiKNtwNhVghBPyvN/view?usp=sharing

## 2. Dependencies:
To run this program, you need to install a few dependencies using pip or conda. This example uses pip.

### *Optional* - Create a python environnement:
#### Create a Virtual Environment
```bash
python -m venv .venv
```

#### Activate the Virtual Environment
**For Windows:**
```powershell
.venv\Scripts\activate
```
**For Linux:**
```bash
source .venv/bin/activate
```

#### Deactivate the Virtual Environment
```bash
deactivate
```

### Install dependencies
1. First, install the PyTorch framework with the following command:
```bash
pip install torch==2.5.1+cu118 torchvision==0.20.1+cu118 --index-url https://download.pytorch.org/whl/cu118
```

2. Then, install additional dependencies from the [requirements.txt](requirements.txt) file:
```bash
pip install -r requirements.txt
```

> **Note:** PyTorch is used for tensor operations and CNN calculations. The dependencies listed in `requirements.txt` are for visualization (e.g., graphics, confusion matrix) and other functionalities.


## 3. Execution
After installing the dependencies, run the program with the following command:
```sh
python main.py
```

You can then choose whether to:
1. Load a pre-trained model, or
2. Train a new model.

Afterward, select the specific test you want to perform with the model.


### Docker (Work in Progress)
![Docker](https://img.shields.io/badge/docker-%230db7ed.svg?style=for-the-badge&logo=docker&logoColor=white)

Image building:
```sh
docker build -t cuda-python-app .
```

Run container image:
```sh
docker run --gpus all -it --rm cuda-python-app
```

---

## Models:


---

## Research:


---