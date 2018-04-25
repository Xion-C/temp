# This config file is used to set configuration

import os

DATA_PATH = 'datasets'

DATASETS = ['facades', 'cityscapes']
CURRENT_DATASET = DATASETS[0]
# CURRENT_DATASET_PATH = os.path.join(DATA_PATH, CURRENT_DATASET)
# CURRENT_DATASET_PATH = os.path.join(os.getcwd(), CURRENT_DATASET_PATH)

LAMBDA_KL = 0.01
LAMBDA_LATENT = 0.5
LAMBDA_IMAGE = 10

LOG_STEP = 100
BATCH_SIZE = 1
IMAGE_SIZE = 256
LATENT_DIMENSION = 8

INSTANCE_NORMALIZATION = False

ENCODER_NETWORKS = ['cnn', 'resnet']
ENCODER_NETWORK = ENCODER_NETWORKS[0]

MODEL_NAME = ''

GPU_INDEX = "0, 1"

SAVE_MODEL_SECONDS = 600
SAVE_SUMMARIES_SECONDS = 30


# --------------------------------------------------------------- #
#
# configuration datastucture
#
class Config(object):
    def __init__(self):
        super(Config, self).__init__()
        self.log_step = LOG_STEP
        self.batch_size = BATCH_SIZE
        self.image_size = IMAGE_SIZE
        self.latent_dim = LATENT_DIMENSION
        self.coeff_reconstruct = LAMBDA_IMAGE
        self.coeff_latent = LAMBDA_LATENT
        self.coeff_kl = LAMBDA_KL
        self.instance_normalization = INSTANCE_NORMALIZATION
        self.gpu = GPU_INDEX
        self.save_model_secs = SAVE_MODEL_SECONDS
        self.save_summaries_secs = SAVE_SUMMARIES_SECONDS
        self.model_name = MODEL_NAME

        self.dataset_path = os.path.join(DATA_PATH, CURRENT_DATASET)
        self.dataset_path = os.path.join(os.getcwd(), self.dataset_path)

        if ENCODER_NETWORK == ENCODER_NETWORKS[0]:
            self.use_resnet = False
        else:
            self.use_resnet = True
