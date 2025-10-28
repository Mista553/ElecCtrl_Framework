#include "infantry_config.h"

Robot_Config_s *InfantryConfigInit(uint8_t robot_id) 
{
    switch (robot_id)
    {
    case INFANTRY_ROBOT_5:
        break;
    default:
        break;
    }
} 

// static Graph_Data_t UI_pitch_line[10]; // pitch准线
// static Graph_Data_t UI_shoot_line[10]; // 射击准线
// static Graph_Data_t UI_shoot_oval[10]; // 瞄准框架
// static Graph_Data_t UI_graph_Arc[3];   // 功率圆弧
// static Graph_Data_t UI_graph_Rectangle[3]; // 绘制射速矩形

// static Graph_Data_t UI_State_dyn[6];  // 机器人状态,动态先add才能change

// static uint32_t shoot_line_location[7] = {460, 380, 300, 538, 538, 959};
// void InfantryStaticUI(referee_info_t *referee_recv_info)
// {
//     // 绘制发射基准线
//     UILineDraw(&UI_shoot_line[0], "sl0", UI_Graph_ADD, 7, UI_Color_Cyan, 2, 1029, shoot_line_location[0], 880, shoot_line_location[0]);
//     UILineDraw(&UI_shoot_line[1], "sl1", UI_Graph_ADD, 7, UI_Color_Cyan, 3, 750, shoot_line_location[1], 1160, shoot_line_location[1]);
//     UILineDraw(&UI_shoot_line[2], "sl2", UI_Graph_ADD, 7, UI_Color_Cyan, 4, 645, shoot_line_location[2], 1274, shoot_line_location[2]);
//     UILineDraw(&UI_shoot_line[3], "sl3", UI_Graph_ADD, 7, UI_Color_Cyan, 4, 600, shoot_line_location[3], 920, shoot_line_location[3]);
//     UILineDraw(&UI_shoot_line[4], "sl4", UI_Graph_ADD, 7, UI_Color_Cyan, 4, 1000, shoot_line_location[4], 1220, shoot_line_location[4]);
//     UIGraphRefresh(&referee_recv_info->referee_id, 5, UI_shoot_line[0], UI_shoot_line[1], UI_shoot_line[2], UI_shoot_line[3], UI_shoot_line[4]);
//     UILineDraw(&UI_shoot_line[5], "sl5", UI_Graph_ADD, 7, UI_Color_Cyan, 4, shoot_line_location[5],300, shoot_line_location[5],505);
//     UIGraphRefresh(&referee_recv_info->referee_id, 1, UI_shoot_line[5]);

//     // 绘制pitch基准线
//     UILineDraw(&UI_pitch_line[0], "so1", UI_Graph_ADD, 7, UI_Color_Cyan, 10, 1320, 538, 1341, 538);
//     UILineDraw(&UI_pitch_line[1], "so2", UI_Graph_ADD, 7, UI_Color_Cyan, 15, 1307, 679, 1258, 651);
//     UILineDraw(&UI_pitch_line[2], "so3", UI_Graph_ADD, 7, UI_Color_Cyan, 10, 1297, 600, 1329, 613);
//     UILineDraw(&UI_pitch_line[3], "so4", UI_Graph_ADD, 7, UI_Color_Cyan, 15, 1191, 768, 1227, 804);
//     UILineDraw(&UI_pitch_line[4], "so5", UI_Graph_ADD, 7, UI_Color_Cyan, 10, 1254, 725, 1282, 742);
//     UIGraphRefresh(&referee_recv_info->referee_id, 5, UI_pitch_line[0], UI_pitch_line[1], UI_pitch_line[2], UI_pitch_line[3], UI_pitch_line[4]); 
    
//     UIArcDraw(&UI_pitch_line[5], "so6", UI_Graph_ADD, 5, UI_Color_Purplish_red, 88, 92, 20, 958, 538, 360, 360);
//     UIGraphRefresh(&referee_recv_info->referee_id, 5, UI_pitch_line[5]);

//     // 绘制功率圆弧
//     UIArcDraw(&UI_graph_Arc[0], "ss0", UI_Graph_ADD, 7, UI_Color_Cyan, 45, 135, 6, 950, 540, 400, 400);
//     UIArcDraw(&UI_graph_Arc[1], "ss1", UI_Graph_ADD, 7, UI_Color_Cyan, 225, 270, 15, 960, 530, 400, 400);
//     UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_graph_Arc[0], UI_graph_Arc[1]);
    
//     UIArcDraw(&UI_graph_Arc[2], "ss2", UI_Graph_ADD, 7, UI_Color_Cyan, 0, 360, 15, 1524, 725, 100, 100);
//     UIGraphRefresh(&referee_recv_info->referee_id, 1, UI_graph_Arc[2]);
//     UIArcDraw(&UI_graph_Arc[3], "ss3", UI_Graph_ADD, 7, UI_Color_Cyan, 0, 0, 15, 1524, 725, 100, 100);
//     UIGraphRefresh(&referee_recv_info->referee_id, 1, UI_graph_Arc[3]);

//     // 绘制射速矩形
//     UIRectangleDraw(&UI_graph_Rectangle[0], "sj1", UI_Graph_ADD, 7, UI_Color_Cyan, 4, 46, 834, 136, 858);

//     UIRectangleDraw(&UI_graph_Rectangle[1], "sj2", UI_Graph_ADD, 7, UI_Color_Cyan, 5, 1481, 672, 1507, 780);
//     UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_graph_Rectangle[0], UI_graph_Rectangle[1]);
//     UIRectangleDraw(&UI_graph_Rectangle[2], "sj3", UI_Graph_ADD, 7, UI_Color_Cyan, 5, 1555, 672, 1581, 780);
//     UIGraphRefresh(&referee_recv_info->referee_id, 1, UI_graph_Rectangle[2]);

//     UILineDraw(&UI_shoot_line[6], "sl6", UI_Graph_ADD, 7, UI_Color_Purplish_red, 4, 1481, 682, 1507, 682);
//     UILineDraw(&UI_shoot_line[7], "sl7", UI_Graph_ADD, 7, UI_Color_Purplish_red, 4, 1555, 682, 1581, 682);
//     UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_shoot_line[6], UI_shoot_line[7]); 
    
// }
// void InfantryDynamciscUI(referee_info_t *referee_recv_info, Referee_Interactive_info_t *_Interactive_data)
// {
//     // // shoot
//     // if (_Interactive_data->Referee_Interactive_Flag.shoot_flag == 1)
//     // {
//     //     // UICharDraw(&UI_State_dyn[2], "sd2", UI_Graph_Change, 8, UI_Color_Pink, 15, 2, 270, 650, _Interactive_data->shoot_mode == SHOOT_ON ? "on " : "off");
//     //     // UICharRefresh(&referee_recv_info->referee_id, UI_State_dyn[2]);

//     //     UIRectangleDraw(&UI_graph_Rectangle[0], "sj1", UI_Graph_ADD, 7, UI_Color_Purplish_red, 4, 46, 834, 136, 858);
//     //     UIRectangleDraw(&UI_graph_Rectangle[1], "sj2", UI_Graph_ADD, 7, UI_Color_Purplish_red, 5, 1481, 672, 1507, 780);
//     //     UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_graph_Rectangle[0], UI_graph_Rectangle[1]);
//     //     UIRectangleDraw(&UI_graph_Rectangle[2], "sj3", UI_Graph_ADD, 7, UI_Color_Purplish_red, 5, 1555, 672, 1581, 780);
//     //     UIGraphRefresh(&referee_recv_info->referee_id, 1, UI_graph_Rectangle[2]);
//     //     _Interactive_data->Referee_Interactive_Flag.shoot_flag = 0;
//     // }
//     if (_Interactive_data->chassis_offset_angle < 180 && _Interactive_data->chassis_offset_angle >= 0)
//         UIArcDraw(&UI_graph_Arc[3], "ss3", UI_Graph_Change, 7, UI_Color_Pink, _Interactive_data->chassis_offset_angle - 10, _Interactive_data->chassis_offset_angle + 10, 15, 1524, 725, 100, 100);
//     else if (_Interactive_data->chassis_offset_angle > -180 && _Interactive_data->chassis_offset_angle < 0)
//         UIArcDraw(&UI_graph_Arc[3], "ss3", UI_Graph_Change, 7, UI_Color_Pink, 360 + (_Interactive_data->chassis_offset_angle - 10), 360 + (_Interactive_data->chassis_offset_angle + 10), 15, 1524, 725, 100, 100);
//     UIGraphRefresh(&referee_recv_info->referee_id, 1, UI_graph_Arc[3]);

//     UIArcDraw(&UI_pitch_line[5], "so6", UI_Graph_Change, 5, UI_Color_Purplish_red, 88 - _Interactive_data->pitch_angle, 92 - _Interactive_data->pitch_angle, 20, 958, 538, 360, 360);
//     UIGraphRefresh(&referee_recv_info->referee_id, 5, UI_pitch_line[5]);

//     if (_Interactive_data->friction_mode == FRICTION_OFF)
//     {
//         UILineDraw(&UI_shoot_line[6], "sl6", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1481, 682, 1507, 682);
//         UILineDraw(&UI_shoot_line[7], "sl7", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1555, 682, 1581, 682);
//         UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_shoot_line[6], UI_shoot_line[7]); 
//     }
//     else 
//     {
//         if (_Interactive_data->bullet_speed == SMALL_AMU_15)
//         {
//             UILineDraw(&UI_shoot_line[6], "sl6", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1481, 712, 1507, 712);
//             UILineDraw(&UI_shoot_line[7], "sl7", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1555, 712, 1581, 712);
//             UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_shoot_line[6], UI_shoot_line[7]); 
//         }
//         else if (_Interactive_data->bullet_speed == SMALL_AMU_18)
//         {
//             UILineDraw(&UI_shoot_line[6], "sl6", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1481, 742, 1507, 742);
//             UILineDraw(&UI_shoot_line[7], "sl7", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1555, 742, 1581, 742);
//             UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_shoot_line[6], UI_shoot_line[7]); 
//         }
//         else
//         {
//             UILineDraw(&UI_shoot_line[6], "sl6", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1481, 772, 1507, 772);
//             UILineDraw(&UI_shoot_line[7], "sl7", UI_Graph_Change, 7, UI_Color_Purplish_red, 4, 1555, 772, 1581, 772);
//             UIGraphRefresh(&referee_recv_info->referee_id, 2, UI_shoot_line[6], UI_shoot_line[7]); 
//         }        
//     }



//     // UILineDraw(&UI_pitch_line[5], "so6", UI_Graph_Change, 5, UI_Color_Purplish_red, 15, 1275, 538, 1310, 538);
//     // UIGraphRefresh(&referee_recv_info->referee_id, 5, UI_pitch_line[5]);
// }