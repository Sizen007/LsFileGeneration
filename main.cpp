#include <iostream>
#include <string>

#include "generate_LS.h"

void find_change(){
    std::vector<int> index;
    std::vector<std::array<double,3>>WPR;
    WPR.push_back({-175.490,109.846,178.523});
    WPR.push_back({-3.561,-70.187,178.521});
    WPR.push_back({-2.375,-73.728,178.287});

    WPR.push_back({-178.638,109.372,178.496});
    WPR.push_back({-0.856,-70.706,178.492});
    WPR.push_back({-0.873,-75.302,178.147});

    WPR.push_back({179.101,109.464,178.502});
    WPR.push_back({1.543,-70.532,178.502});
    WPR.push_back({1.459,-74.922,178.183});

    WPR.push_back({7.392,-83.369,176.419});
    WPR.push_back({173.089,97.107,176.629});
    WPR.push_back({173.210,99.199,177.295});

    int past_negative_cnt = 0;
    for(int i = 0; i < WPR.size(); i++){
        int negative_cnt = 0;
        for(int j = 0; j < 3; j++){
            if(WPR[i][j] < 0) negative_cnt++;
        }
        if(negative_cnt != past_negative_cnt) index.push_back(i);
        past_negative_cnt = negative_cnt;
    }
    for(int i = 0; i < index.size(); i++){
        std::cout<<index[i]<<std::endl;
    }
}

void test_ls(){
    std::vector<std::array<double,7>> pos;

    for(int i = 0; i < 5; i++){
        pos.push_back({1.000,2.000,3.000,4.000,5.000,6.000,7.000});
    }

    fanuc_post_processor::generate_LS program;
    program.program_name_ = "HUAB";
    program.comment_ = "\"\"";
    program.prog_size_ = "4757";
    program.file_name_ = "HUAB";
    program.version_ = "0";
    program.memory_size_ = "5089";
    program.pos_ = pos;
    program.velocity_ = "200";
    program.cnt_ = "CNT60";
    program.get_pos_size();

    program.First_Part();
    //DIY Part
    program.motion_add("\t3:\t;");
    //program.motion_add("\t4:  DO[22:MOJI]=ON\t;");
    program.left_command();
    program.POS_Part();
    //std::cout<<program.line_cnt<<std::endl;
    program.write();
    program.display();
}

void test(){
    Eigen::AngleAxisd rotation_vector(M_PI/4,Eigen::Vector3d(0,0,1));

    Eigen::Matrix3d rotation_matrix1 = Eigen::Matrix3d::Identity();
    rotation_matrix1 = rotation_vector.matrix();
    std::cout<<"rotation matrix is: "<<std::endl;
    std::cout<<rotation_matrix1<<std::endl;

    Eigen::Matrix3d rotation_matrix4;
    Eigen::Quaterniond quaternion4(0.92388,0,0,0.382683);

    rotation_matrix4 = quaternion4.matrix();

    int a = 1000 + 10000 + 14000 - 7000 - 13000 - 14000 -14000 + 3500 + 3500 + 3500;
    std::cout<<"a is: "<<a<<std::endl;
}

int main() {
    //test_ls();
    //find_change();

    test();

    return 0;
}
