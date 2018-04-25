# BicycleGAN implementation
Clemson CPSC-8100 project
by Ziyun Zhang (ziyunz@clemson.edu) & Xin Cheng (xcheng2@clemson.edu)

## Dependencies
- Linux
- Tensorflow 1.6.0
- NumPy
- SciPy
- Pillow
- h5py

## Configurations
The runtime arguments are explained as follows:
- LOG_STEP: Tensorboard log frequency, default is 100
- IMAGE_SIZE: Input image size, default is 256
- LATENT_DIMENSION: Dimensionality of the latent vector, default is 8
- LAMBDA_IMAGE: Loss coefficient for reconstruct, default is 10
- LAMBDA_LATENT: Loss coefficient for latent cycle, defaut is 0.5
- LAMBDA_KL: Loss coefficient for KL divergence, default is 0.01
- INSTANCE_NORMALIZATION: Whether use instance normalize instead of batch normalize, default is False
- ENCODER_NETWORK: Use CNN or ResNet for the encoder, default is CNN
- GPU_INDEX: GPU index for CUDA_VISIBLE_DEVICES, default is 1
- DATA_PATH: The location of the dataset.
- CURRENT_DATASET: Current training and testing dataset
- SAVE_MODEL_SECONDS: Time interval of saving model in training session
- SAVE_SUMMARIES_SECONDS: Time interval of saving summaries in training session


## Usage
- Download dataset(e.g., facades)
```bash
bash download_dataset.sh facades
```
- Training and testing
```python
python train.py
```
- The log files and trained model(.ckp) located in ./logs
- The testing result images located in ./results

## Reference:
[1] Zhu JY, Zhang R, Pathak D, Darrell T, Efros AA, Wang O, Shechtman E. Toward multimodal image-to-image translation. InAdvances in Neural Information Processing Systems 2017 (pp. 465-476).
[2] Isola P, Zhu JY, Zhou T, Efros AA. Image-to-image translation with conditional adversarial networks. arXiv preprint. 2017 Jul 1.
[3] Zhu JY, Park T, Isola P, Efros AA. Unpaired image-to-image translation using cycle-consistent adversarial networks. arXiv preprint arXiv:1703.10593. 2017 Oct 1.

