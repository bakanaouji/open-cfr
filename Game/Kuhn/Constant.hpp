//
// Created by 阿部 拳之 on 2019/10/25.
//

#ifndef REGRETMINIMIZATION_CONSTANT_HPP
#define REGRETMINIMIZATION_CONSTANT_HPP

namespace Kuhn {

static const int PlayerNum = 2;
static const int CardNum = PlayerNum + 1;
static constexpr int ChanceActionNum() {
    int actionNum = 1;
    for (int i = 0; i < CardNum; ++i) {
        actionNum *= (i + 1);
    }
    return actionNum;
}

}

#endif //REGRETMINIMIZATION_CONSTANT_HPP
