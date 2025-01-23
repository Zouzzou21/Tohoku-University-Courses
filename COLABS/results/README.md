This folder is my results with different epoch:
- [model_e1](model_e1/) is the results for the model train with 1 epoch
- [model_e10](model_e10/) is the results for the model train with 10 epoch
- [model_e100](model_e100/) is the results for the model train with 100 epoch
- [model_e1000](model_e1000/) is the results for the model train with 1000 epoch
- [resnet-18_e100](resnet-18_e100/) is the results for the ResNet-18 model train with 100 epoch
- [mobilenet-v2_e100](mobilenet-v2_e100/) is the results for the MobilNet-v2 model train with 100 epoch

The pre-trained models can be found on the following Google Drive: https://drive.google.com/file/d/1djip6a5tOb3r8YZXNFj6JAhi5rRDQOQV/view?usp=sharing

The pictures use for my test are:
- Glioma tumor : [Te-gl_0010.jpg](Te-gl_0010.jpg) (data/glioma/Te-gl_0010.jpg)
- Meningioma tumor : [Te-me_0010.jpg](Te-me_0010.jpg) (data/meningioma/Te-me_0010.jpg)
- No tumor : [Te-no_0010.jpg](Te-no_0010.jpg) (data/notumor/Te-no_0010.jpg)
- Pituitary tumor: [Te-pi_0010.jpg](Te-pi_0010.jpg) (data/pituitary/Te-pi_0010.jpg)

For `test_model_with_confusion_matrix`:
No Tumor = `notumor`, Tumor Type 1 = `glioma`, Tumor Type 2 = `meningioma`, Tumor Type 3 = `pituitary`