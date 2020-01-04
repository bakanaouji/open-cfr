//
// Created by 阿部 拳之 on 2019-08-05.
//

#include "Node.hpp"

#include <iomanip>
#include <sstream>
#include <iostream>

namespace Trainer {

Node::Node(const int actionNum) : mActionNum(actionNum), mAlreadyCalculated(false) {
    mRegretSum = new float[actionNum];
    mStrategy = new float[actionNum];
    mStrategySum = new float[actionNum];
    mAverageStrategy = new float[actionNum];
    for (int a = 0; a < actionNum; ++a) {
        mRegretSum[a] = 0.0;
        mStrategy[a] = 0.0;
        mStrategySum[a] = 0.0;
        mAverageStrategy[a] = 0.0;
    }
}

Node::~Node() {
    delete[] mRegretSum;
    delete[] mStrategy;
    delete[] mStrategySum;
    delete[] mAverageStrategy;
}

void Node::calcAverageStrategy() {
    // すでに計算済みであればスキップ
    if (mAlreadyCalculated) {
        return;
    }
    for (int a = 0; a < mActionNum; ++a) {
        mAverageStrategy[a] = 0.0;
    }
    float normalizingSum = 0.0;
    for (int a = 0; a < mActionNum; ++a) {
        normalizingSum += mStrategySum[a];
    }
    for (int a = 0; a < mActionNum; ++a) {
        if (normalizingSum > 0) {
            mAverageStrategy[a] = mStrategySum[a] / normalizingSum;
        } else {
            mAverageStrategy[a] = 1.0 / (float) mActionNum;
        }
    }
    mAlreadyCalculated = true;
}

const float *Node::strategy() {
    float normalizingSum = 0.0;
    for (int a = 0; a < mActionNum; ++a) {
        mStrategy[a] = mRegretSum[a] > 0 ? mRegretSum[a] : 0;
        normalizingSum += mStrategy[a];
    }
    for (int a = 0; a < mActionNum; ++a) {
        if (normalizingSum > 0) {
            mStrategy[a] /= normalizingSum;
        } else {
            mStrategy[a] = 1.0 / (float) mActionNum;
        }
    }
    return mStrategy;
}

const float *Node::averageStrategy() const {
    assert(mAlreadyCalculated);
    return mAverageStrategy;
}

void Node::strategySum(const float *strategy, const float realizationWeight) {
    for (int a = 0; a < mActionNum; ++a) {
        mStrategySum[a] += realizationWeight * strategy[a];
    }
    mAlreadyCalculated = false;
}

float Node::regretSum(const int action) const {
    return mRegretSum[action];
}

void Node::regretSum(const int action, const float value) {
    mRegretSum[action] = value;
}

uint8_t Node::actionNum() const {
    return mActionNum;
}

} // namespace
