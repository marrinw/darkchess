#ifndef CHESSMAN_H
#define CHESSMAN_H

class chessman{
    private:
    int id;    //null =0,shuai=1,shi=2,xiang=3,che=4,ma=5,pao=6,bing=7
    bool side;          //red=0,black=1;
    bool visible;
    public:
    int getid();
    bool getside();
    bool getvisible();
    void changeid(int id);
    void changeside(bool side);
    void changevisible(bool visible);
    void initialize(int id,bool side);
};

#endif // CHESSMAN_H
