//
// Created by sizen on 2021/3/29.
//

#ifndef GENERATE_LS_GENERATE_LS_H
#define GENERATE_LS_GENERATE_LS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace fanuc_post_processor
{
    class generate_LS{
    public:
        using ProgramText = std::string;
        ProgramText program;
        std::string program_name_;
        std::string comment_;
        std::string prog_size_;
        //std::string create_data_;
        //std::string modified_data_;
        std::string file_name_;
        std::string version_;
        int line_cnt = 0;
        std::string memory_size_;
        int MN_cnt = 0;
        std::string velocity_;
        std::string cnt_;


        std::string PATH;
        std::vector<std::array<double,7>> pos_;

        void First_Part();

        void motion_add(std::string command);
        void get_pos_size();
        void read_pos();

        void left_command();
        void POS_Part();

        void display();
        void write();

    };

    void generate_LS::motion_add(std::string command) {
        MN_cnt++;
        line_cnt ++;
        program.append(command);
        program.append("\n");
    }

    void generate_LS::get_pos_size() {
        line_cnt += pos_.size();
    }


    void generate_LS::read_pos() {
        for(int i = 0; i < pos_.size(); i++){
            Eigen::Quaterniond quaternion4(pos_[i][6],pos_[i][3],pos_[i][4],pos_[i][5]);
            Eigen::Vector3d eulerAngle = quaternion4.matrix().eulerAngles(2,1,0); // zyx
            double angle_W = eulerAngle[2]/M_PI*180;
            double angle_P = eulerAngle[1]/M_PI*180;
            double angle_R = eulerAngle[0]/M_PI*180;
            program.append("P[");
            program.append(std::to_string(i+1));
            program.append("]{");
            program.append("\n");
            program.append("   GP1:");
            program.append("\n");
            program.append("\tUF : 0, UT : 1,\t\tCONFIG : 'N U T, 0, 0, 0',");
            program.append("\n");
            program.append("\tX =\t");
            program.append(std::to_string(pos_[i][0]));
            program.append("\tmm,\tY =\t");
            program.append(std::to_string(pos_[i][1]));
            program.append("\tmm,\tZ =\t");
            program.append(std::to_string(pos_[i][2]));
            program.append("\tmm,");
            program.append("\n");
            // *********************** wpr = zyx？ *******************
            program.append("\tW =\t");
            program.append(std::to_string(angle_W));
            program.append("\tdeg,\tP =\t");
            program.append(std::to_string(angle_P));
            program.append("\tdeg,\tR =\t");
            program.append(std::to_string(angle_R));
            program.append("\tdeg");
            program.append("\n");
            program.append("};");
            program.append("\n");
        }

    }

    void generate_LS::First_Part() {
        // PROG
        program.append("/PROG ");
        program.append(program_name_);
        program.append("\n");
        // ATTR
        program.append("/ATTR");
        program.append("\n");
        program.append("OWNER\t\t\t= MNEDITOR;");
        program.append("\n");
        program.append("COMMENT\t\t\t= " + comment_ +";");
        program.append("\n");
        program.append("PROG_SIZE\t\t= " + prog_size_ + ";");
        program.append("\n");
//        program.append("CREATE\t\t\t= DATE 21-03-18  TIME 13:17:58;");
//        program.append("\n");
//        program.append("MODIFIED\t\t= DATE 21-03-18  TIME 14:10:54;");
//        program.append("\n");
        program.append("FILE_NAME\t\t= " + file_name_ + ";");
        program.append("\n");
        program.append("VERSION\t\t\t= " + version_ + ";");
        program.append("\n");
        program.append("LINE_COUNT\t\t= " + std::to_string(line_cnt) + ";");
        program.append("\n");
        program.append("MEMORY_SIZE\t\t= " + memory_size_ + ";");
        program.append("\n");
        program.append("PROTECT\t\t\t= READ_WRITE;");
        program.append("\n");
        program.append("TCD:  STACK_SIZE\t\t= 0,\n"
                       "      TASK_PRIORITY\t\t= 50,\n"
                       "      TIME_SLICE\t\t= 0,\n"
                       "      BUSY_LAMP_OFF\t\t= 0,\n"
                       "      ABORT_REQUEST\t\t= 0,\n"
                       "      PAUSE_REQUEST\t\t= 0;");
        program.append("\n");
        program.append("DEFAULT_GROUP\t= 1,*,*,*,*;");
        program.append("\n");
        program.append("CONTROL_CODE\t= 00000000 00000000;");
        program.append("\n");

//        //APPL
//        program.append("/APPL\n");
//        program.append("  SPOT : TRUE ;");
//        program.append("\n");
//        program.append("\n");
//        program.append("AUTO_SINGULARITY_HEADER;");
//        program.append("\n");
//        program.append("  ENABLE_SINGULARITY_AVOIDANCE   : FALSE;");
//        program.append("\n");
//        program.append("  SPOT Welding Equipment Number : 1 ;");
//        program.append("\n");

        //MN
        program.append("/MN");
        program.append("\n");
        program.append("\t1:  UFRAME_NUM=0 ;");
        program.append("\n");
        program.append("\t2:  UTOOL_NUM=1 ;");
        program.append("\n");
    }

    void generate_LS::left_command() {
        line_cnt = line_cnt - pos_.size() + 2;
        for(int i = 0; i < pos_.size(); i++){
            program.append("\t"+std::to_string(i+line_cnt+1)+":L"+" P["+std::to_string(i+1)+"] "+velocity_+"mm/sec "+cnt_+";\n");

        }
        line_cnt += pos_.size();
    }

    void generate_LS::POS_Part() {
        program.append("/POS");
        program.append("\n");
        read_pos();
        program.append("\n");
        program.append("/END");
    }

    void generate_LS::write() {
        std::ofstream output_file;
        output_file.open("/home/sizen/CLionProjects/generate_LS/pos.ls");
        if(output_file.fail()) std::cout<<"cannot open file !!!"<<std::endl;
        output_file<<program;
        output_file.close();

    }

    void generate_LS::display() {
        std::cout<<program<<std::endl;
    }

}


#endif //GENERATE_LS_GENERATE_LS_H
