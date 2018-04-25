# Code adapted from Youngwoon Lee:
# https://github.com/gitlimlab/BicycleGAN-Tensorflow

import sys
import os
from datetime import datetime

import tensorflow as tf

from config import Config
from data_processing import get_data
from BicycleGAN.model import BicycleGAN

class FastSaver(tf.train.Saver):
    def save(self, sess, save_path, global_step=None, latest_filename=None,
             meta_graph_suffix="meta", write_meta_graph=True):
        super(FastSaver, self).save(sess, save_path, global_step, latest_filename,
                                    meta_graph_suffix, False)

def main(_):
    cfg = Config()
    # setting GPU
    os.environ['CUDA_DEVICE_ORDER'] = "PCI_BUS_ID"
    os.environ['CUDA_VISIBLE_DEVICES'] = cfg.gpu

    print('Data loading...')
    print(cfg.dataset_path)
    train_A, train_B, test_A, test_B = get_data(cfg.dataset_path, 'facades',cfg.image_size)

    # load graph
    model = BicycleGAN(cfg)
    print('- Graph loaded')

    log_dir = './logs'
    if not os.path.exists(log_dir):
        os.makedirs(log_dir)
    model_name = os.path.basename(cfg.dataset_path)
    model_name += '_%s' % datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    log_dir = os.path.join(log_dir, model_name)
    print('- Events dirctory: %s' % (log_dir))

    summary_writer = tf.summary.FileWriter(log_dir)

    results_dir = './results'
    if not os.path.exists(results_dir):
        os.makedirs(results_dir)

    vars_save = tf.global_variables()
    vars_init = tf.variables_initializer(vars_save)
    vars_global_init = tf.global_variables_initializer()
    saver = FastSaver(vars_save)
    vars_list = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,
                             tf.get_variable_scope().name)
    for v in vars_list:
        print('%s - %s' % (v.name, v.get_shape()))

    def init_fn(sess):
        print('- Initializing all parameters.')
        sess.run(vars_global_init)

    sv = tf.train.Supervisor(is_chief=True,
                             logdir=log_dir,
                             saver=saver,
                             summary_op=None,
                             init_op=vars_init,
                             init_fn=init_fn,
                             summary_writer=summary_writer,
                             ready_op=tf.report_uninitialized_variables(vars_save),
                             global_step=model.global_step,
                             save_model_secs=cfg.save_model_secs,
                             save_summaries_secs=cfg.save_summaries_secs)

    print('*** Training session start ***')
    with sv.managed_session() as sess:
        model.train(sess, summary_writer, train_A, train_B)
    print('Training complete!')

    print('*** Testing session start ***')
    with sv.managed_session() as sess:
        base_dir = os.path.join('results', model_name)
        if not os.path.exists(base_dir):
            os.makedirs(base_dir)
        model.test(sess, test_A, test_B, base_dir)


if __name__ == "__main__":
    tf.app.run()
