// SPDX-License-Identifier: Apache-2.0-only
/**
 * Copyright (C) 2020 Jihoon Lee <jhoon.it.lee@samsung.com>
 *
 * @file unittest_nntrainer_modelfile.cpp
 * @date 16 July 2020
 * @brief NNTrainer datafile parmeterized tester.
 * @see	https://github.com/nnstreamer/nntrainer
 * @author Jihoon Lee <jhoon.it.lee@samsung.com>
 * @bug No known bugs except for NYI items
 */

#include "nntrainer_test_util.h"
#include <gtest/gtest.h>
#include <neuralnet.h>

/**
 * @brief check given ini is failing/suceeding at load
 */
TEST_P(nntrainerIniTest, load_config) {
  int status = NN.loadFromConfig();

  if (failAtLoad()) {
    EXPECT_NE(status, ML_ERROR_NONE);
  } else {
    EXPECT_EQ(status, ML_ERROR_NONE);
  }
}

/**
 * @brief check given ini is failing/succeeding at init
 */
TEST_P(nntrainerIniTest, init) {
  int status = NN.loadFromConfig();

  if (failAtLoad()) {
    ASSERT_NE(status, ML_ERROR_NONE);
  } else {
    ASSERT_EQ(status, ML_ERROR_NONE);
  }
  status = NN.init();

  if (failAtInit()) {
    EXPECT_NE(status, ML_ERROR_NONE);
  } else {
    EXPECT_EQ(status, ML_ERROR_NONE);
  }
}

/// @todo add run test could be added with iniTest flag to control skip

static IniSection nw_base("network", "Type = NeuralNetwork | "
                                     "minibatch = 32 | "
                                     "epsilon = 1e-7 | "
                                     "cost = cross");
static IniSection adam("adam", "Optimizer = adam |"
                               "Learning_rate = 0.00001 |"
                               "Decay_rate = 0.96 |"
                               "Decay_steps = 1000");

static IniSection nw_adam = nw_base + adam;

static IniSection dataset("DataSet", "BufferSize = 100 |"
                                     "TrainData = trainingSet.dat | "
                                     "TestData = testSet.dat |"
                                     "ValidData = valSet.dat |"
                                     "LabelData = label.dat");

static IniSection input("inputlayer", "Type = input |"
                                      "Input_Shape = 32:1:1:62720 |"
                                      "bias_init_zero = true |"
                                      "Normalization = true |"
                                      "Activation = sigmoid");

static IniSection out("fclayer", "Type = fully_connected |"
                                 "Unit = 10 |"
                                 "bias_init_zero = true |"
                                 "Activation = softmax");

static IniSection conv2d("conv2d", "Type = conv2d |"
                                   "bias_init_zero = true |"
                                   "Activation = sigmoid |"
                                   "filter = 6 |"
                                   "kernel_size = 5,5 |"
                                   "stride = 1,1 |"
                                   "padding = 0,0 |");

static int SUCCESS = 0;
static int LOADFAIL = initest::LOAD;
static int INITFAIL = initest::INIT;
static int ALLFAIL = LOADFAIL | INITFAIL;

using I = IniSection;
// clang-format off
INSTANTIATE_TEST_CASE_P(
  nntrainerIniAutoTests, nntrainerIniTest, ::testing::Values(
    mkIniTc("basic_p", {nw_adam, input, out}, SUCCESS),
    mkIniTc("basic_dataset_p", {nw_adam, dataset, input, out}, SUCCESS),
    /**< @note After #316 resolve, following TC should pass
    mkIniTc("no_net_sec_name_n", {I(nw_adam, "-", "")}, ALLFAIL),
    mkIniTc("no_network_sec_n", {input, out}, ALLFAIL),
    mkIniTc("empty_n", {}, ALLFAIL),
    mkIniTc("wrong_opt_type_n", {nw_adam + "Optimizer = wrong_opt", input, out),
    mkIniTc("adam_neg_lr_n", {nw_adam + "learning_rate = -0.1", input, out}, ALLFAIL),
    mkIniTc("no_cost_n", {nw_adam + "-cost", input, out}, ALLFAIL)
    */
    mkIniTc("no_trainingSet_p", {nw_adam, dataset + "-TrainData", input, out}, SUCCESS),
    mkIniTc("no_testSet_p", {nw_adam, dataset + "-TestData", input, out}, SUCCESS),
    mkIniTc("no_validSet_p", {nw_adam, dataset + "-ValidData", input, out}, SUCCESS),
    mkIniTc("no_labelSet_p", {nw_adam, dataset + "-LabelData", input, out}, SUCCESS),
    mkIniTc("basic_conv2d_p", {nw_adam, conv2d + "input_shape = 32:1:1:62720"}, SUCCESS)
));
// clang-format on

/**
 * @brief Main gtest
 */
int main(int argc, char **argv) {
  int result = -1;

  try {
    testing::InitGoogleTest(&argc, argv);
  } catch (...) {
    std::cerr << "Error duing IniGoogleTest" << std::endl;
    return 0;
  }

  try {
    result = RUN_ALL_TESTS();
  } catch (...) {
    std::cerr << "Error duing RUN_ALL_TSETS()" << std::endl;
  }

  return result;
}
