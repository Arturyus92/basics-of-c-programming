struct data {
    int year, month, day, hour, minut;
    float t;
};

struct temperature {
    float sum;
    int count;
    struct data max, min;
};


float mean_temp_month(float, int);
void statistics_year(float []);