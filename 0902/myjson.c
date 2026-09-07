#include "myhead.h"

int main(int argc, char const *argv[])
{
    char *jsondata="{\"影片名字\":\"疯狂的石头\",\"票价\":29.9,\"上映时间\":\"2026-9-1\",\"影片的主要演员\":{\"一号男\":\"刘德华\",\"二号男\":\"梁朝伟\",\"一号女\":\"舒淇\"}}";
    
    cJSON *json1=cJSON_Parse(jsondata);

    cJSON *val1=cJSON_GetObjectItem(json1,"影片名字");
    cJSON *val2=cJSON_GetObjectItem(json1,"票价");
    cJSON *val3=cJSON_GetObjectItem(json1,"上映时间");
    cJSON *val4=cJSON_GetObjectItem(json1,"影片的主要演员");

    // cJSON *json2=cJSON_Parse(val4->valuestring);
    cJSON *val4_1=cJSON_GetObjectItem(val4,"一号男");
    cJSON *val4_2=cJSON_GetObjectItem(val4,"二号男");
    cJSON *val4_3=cJSON_GetObjectItem(val4,"一号女");

    printf("影片名字:%s,\n",val1->valuestring);
    printf("票价:%lf,\n",val2->valuedouble);
    printf("上映时间:%s,\n",val3->valuestring);
    printf("影片的主要演员:\n");
    printf("{男一号:%s,\n",val4_1->valuestring);
    printf(" 男一号:%s,\n",val4_2->valuestring);
    printf(" 女一号:%s}\n",val4_3->valuestring);


    return 0;
}
