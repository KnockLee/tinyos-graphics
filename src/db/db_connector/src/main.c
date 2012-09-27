#include "../include/sensor.h"

int main(int argc,char *argv[])
{
    MYSQL mysql;
    db_connect_info_t db_connect_info;

    node_t      node_inser_info;
    sensor_t    sensor_inser_info;
    network_t   network_inser_info;
    memset(&node_inser_info,0,sizeof(node_t));
    memset(&sensor_inser_info,0,sizeof(sensor_t));
    memset(&network_inser_info,0,sizeof(network_t));
    
    node_t      node_info[10000];
    sensor_t    sensor_info[10000];
    network_t   network_info[10000];
    memset(&node_info,0,sizeof(node_info));
    memset(&sensor_info,0,sizeof(sensor_info));
    memset(&network_info,0,sizeof(network_info));

    //strcpy(db_connect_info.host,"127.0.0.1");
    //strcpy(db_connect_info.user,"root");
    //strcpy(db_connect_info.password,"arnold");
    //strcpy(db_connect_info.db_name,"test4");

    //strcpy(db_connect_info.host,"10.18.38.14");
    //strcpy(db_connect_info.host,"10.18.46.163");
    //strcpy(db_connect_info.user,"tinyos");
    //strcpy(db_connect_info.password,"njjizyj0826");
    //strcpy(db_connect_info.db_name,"test4");

    strcpy(db_connect_info.host,"10.18.46.111");
    strcpy(db_connect_info.user,"tinyos");
    strcpy(db_connect_info.password,"tinyos");
    strcpy(db_connect_info.db_name,"test5");
    if(get_db_handler(&mysql,db_connect_info) == -1){
        return -1;
    }
    int num = 0;
    
    long i,j;
    
    //j = get_all_record(&mysql,sensor_info);
    //j = get_network_info(&mysql,network_info);
    //j = get_all_node_info(&mysql,node_info);
    //j = get_latest_record(&mysql,sensor_info,"10.18.46.188:1234",2,"temperature");
    //j = get_absolute_record(&mysql,sensor_info,"10.16.17.0",99,"temp","2012-09-23 11:21:41","2012-09-23 11:21:42");
    while(1){
    j = get_relative_record(&mysql,sensor_info,"10.16.17.0",99,"sound","20120925082929",-30);
    printf("j = %ld\n",j);
    if(j==-1){
        mysql_close(&mysql);
        return -1;
    }
    else{
        for(i = 0;i < j;i++){

            printf("network_id:%d\t"       ,sensor_info[i].network_id);
            printf("network_name:%s\t"     ,sensor_info[i].network_name);
            printf("node_id:%d\t"          ,sensor_info[i].node_id);
            printf("temp:%6.2lf\t"         ,sensor_info[i].temp);
            printf("photo:%6.2lf\t"        ,sensor_info[i].photo);
            printf("insert_time:%s\t"      ,sensor_info[i].time);
            printf("\n");
        }
    }
    j = get_latest_record(&mysql,sensor_info,"10.16.17.0",99,"temp");
    if(j==-1){
        mysql_close(&mysql);
        return -1;
    }
    else{
        for(i = 0;i < j;i++){
            //printf("network_id:%d \t"      ,node_info[i].network_id);
            //printf("network_name:%s \t"    ,node_info[i].network_name);
            //printf("node_id:%d\t"          ,node_info[i].node_id);
            //printf("parent_id:%d\t"        ,node_info[i].parent_id);
            //printf("power:%d\t"            ,node_info[i].power);
            //printf("position_x:%6.2lf\t"   ,node_info[i].position.x);
            //printf("position_y:%6.2lf\t"   ,node_info[i].position.y);

            //printf("network_id:%d \t"        ,network_info[i].network_id);
            //printf("network_name:%s \t"      ,network_info[i].network_name);
            //printf("node_id:%d \t"           ,network_info[i].node_id);
            //printf("parent_id:%d \t"         ,network_info[i].parent_id);
            //printf("quality:%d \t"           ,network_info[i].quality);

            printf("network_id:%d\t"       ,sensor_info[i].network_id);
            printf("network_name:%s\t"     ,sensor_info[i].network_name);
            printf("node_id:%d\t"          ,sensor_info[i].node_id);
            printf("temp:%6.2lf\t"         ,sensor_info[i].temp);
            printf("photo:%6.2lf\t"        ,sensor_info[i].photo);
            //printf("sound:%6.2lf\t"        ,sensor_info[i].sound);
            //printf("x_acc:%6.2lf\t"        ,sensor_info[i].x_acc);
            //printf("y_acc:%6.2lf\t"        ,sensor_info[i].y_acc);
            //printf("x_mag:%6.2lf\t"        ,sensor_info[i].x_mag);
            //printf("y_mag:%6.2lf\t"        ,sensor_info[i].y_mag);
            printf("insert_time:%s\t"      ,sensor_info[i].time);
            printf("\n");
        }
    }
    sleep(1);
    }
    mysql_close(&mysql);
    return 0;
}
