#include "myhead.h"
#include "cJSON.h" //CJSON库的头文件

int main(int argc, char const *argv[])
{
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddStringToObject(obj, "影片名字", "疯狂的石头");
    cJSON_AddNumberToObject(obj, "票价", 29.9);
    cJSON_AddStringToObject(obj, "上映时间", "2026-9-1");
    cJSON *obj1 = cJSON_CreateObject();
    cJSON_AddStringToObject(obj1, "一号男", "刘德华");
    cJSON_AddStringToObject(obj1, "二号男", "梁朝伟");
    cJSON_AddStringToObject(obj1, "一号女", "舒淇");
    cJSON_AddItemToObject(obj, "影片的主要演员", obj1);
    cJSON *array = cJSON_CreateArray();
    cJSON_AddItemToArray(array, cJSON_CreateString("华纳"));
    cJSON_AddItemToArray(array, cJSON_CreateString("华谊兄弟"));
    cJSON_AddItemToArray(array, cJSON_CreateString("万达影业"));
    cJSON_AddItemToObject(obj, "影片发行方", array);

    char *out = cJSON_Print(obj);
    printf("%s\n", out);

    cJSON_free(out);
    cJSON_Delete(obj);

    return 0;
}
