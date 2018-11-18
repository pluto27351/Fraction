#include "fraction.h"

fraction::fraction(int uni,int queNo, int number){
    Node * answer;
    
    int u = uni * 10 + queNo;
    switch(u){
        case 11:
        case 12:    //測試用
        case 13:    //測試用
        case 14:    //測試用
        case 15:    //測試用
        case 16:    //測試用
            answer = CSLoader::createNode("ans/u1_1.csb");
            Input_u1(*answer, number);
            break;
        case 21:    //測試用
        case 24:
            answer = CSLoader::createNode("ans/u2_4.csb");
            Input_u2_4(*answer, number);
            break;
        case 22:    //測試用
        case 27:
            answer = CSLoader::createNode("ans/u2_7.csb");
            Input_u2_7(*answer, number);
            break;
        case 31:    //測試用
        case 32:
            answer = CSLoader::createNode("ans/u3_2.csb");
            Input_u3_2(*answer, number);
            break;
    }
    answer->setPosition(Point(1024,700));
   // answer->setPosition(Point(480,320));
    addChild(answer);
}

void fraction::Input_u1(Node &Q, int number){
    char Input[5];
    //取得擺放位子
    //國字
    Text* Output_c = (Text*)Q.getChildByName("C_1");
    Output_c->setString(chiness[number-2]);
    //Output_c->setScale(2);
    
    //數字
    for(int i = 0;i<2;i++){
        sprintf(Input,"N_%d",i+1);
        Text *Output_n = (Text *)Q.getChildByName(Input);
        sprintf(Input,"%d",number);
        Output_n->setString(Input);
        //Output_n->setScale(2);
    }
    
    //分數
    for(int i = 0;i<3;i++){
        sprintf(Input,"F_%d",i+1);
        Node *Output_f = (Node *)Q.getChildByName(Input);
        sprintf(Input,"%d",number);
        if(i < 2)
            Output_f->addChild(Set_fraction("1", Input, "0"));
        else
            Output_f->addChild(Set_fraction(Input, Input, "0"));
    }
    
    //運算式
    Node *Output_af = Q.getChildByName("AF_1");
    Output_af->addChild(FractionOperation(number));
}

void fraction::Input_u2_4(Node &Q, int number){
    char Input[5];
    char I2[5];
    //取得擺放位子
    //國字
    Text* Output_c = (Text*)Q.getChildByName("C_1");
    Output_c->setString(chiness[number-2]);
   // Output_c->setScale(2);
    
    //數字
    for(int i = 0;i<2;i++){
        sprintf(Input,"N_%d",i+1);
        Text *Output_n = (Text *)Q.getChildByName(Input);
        sprintf(Input,"%d",number);
        Output_n->setString(Input);
        //Output_n->setScale(2);
    }
    
    //分數
    for(int i = 0;i<9;i++){
        sprintf(Input,"F_%d",i+1);
        Node *Output_f = (Node *)Q.getChildByName(Input);

        sprintf(Input,"%d",number);
        if(i < 2)
            Output_f->addChild(Set_fraction("1", Input, "0"));
        else if(i < 6)
            Output_f->addChild(Set_fraction(Input, Input, "0"));
        else if(i < 8){
            sprintf(I2,"%d",number*2);
            Output_f->addChild(Set_fraction(I2, Input, "0"));
        }
        else{
            sprintf(I2,"%dx2",number);
            Output_f->addChild(Set_fraction(I2, Input, "0"));
        }
    }
}

void fraction::Input_u2_7(Node &Q, int number){
    char Input[5];
    //取得擺放位子
    //國字
    Text* Output_c = (Text*)Q.getChildByName("C_1");
    Output_c->setString(chiness[number-2]);
   // Output_c->setScale(2);
    
    //數字
    for(int i = 0;i<3;i++){
        sprintf(Input,"N_%d",i+1);
        Text *Output_n = (Text *)Q.getChildByName(Input);
        sprintf(Input,"%d",number);
        Output_n->setString(Input);
      // Output_n->setScale(2);
    }
    
    //分數
    for(int i = 0;i<11;i++){
        sprintf(Input,"F_%d",i+1);
        Node *Output_f = (Node *)Q.getChildByName(Input);
        sprintf(Input,"%d",number);
        if(i < 6)
            Output_f->addChild(Set_fraction("1", Input, "0"));
        else if(i < 9)
            Output_f->addChild(Set_fraction("4", Input, "0"));
        else
            Output_f->addChild(Set_fraction("4", Input, "2"));
    }
}

void fraction::Input_u3_2(Node &Q, int number){
    char Input[5];
    char I2[5];
    //取得擺放位子
    //數字
    Text *Output_n = (Text *)Q.getChildByName("N_1");
    sprintf(Input,"%d",number*4+2);
    Output_n->setString(Input);
    //Output_n->setScale(2);
    
    //分數
    for(int i = 0;i<9;i++){
        sprintf(Input,"F_%d",i+1);
        Node *Output_f = (Node *)Q.getChildByName(Input);
        sprintf(Input,"%d",number);
        switch(i){
            case 0:
            case 1:
                sprintf(I2,"%dx4",number);
                Output_f->addChild(Set_fraction(I2, Input, "0"));
                break;
            case 2:
                sprintf(I2,"%d",number*4);
                Output_f->addChild(Set_fraction(I2, Input, "0"));
                break;
            case 3:
                Output_f->addChild(Set_fraction("2", Input, "4"));
                break;
            case 4:
                Output_f->addChild(Set_fraction("2", Input, "0"));
                break;
            case 5:
                sprintf(I2,"%d+2",number*4);
                Output_f->addChild(Set_fraction(I2, Input, "0"));
                break;
            case 6:
            case 7:
                sprintf(I2,"%d",number*4+2);
                Output_f->addChild(Set_fraction(I2, Input, "0"));
                break;
            case 8:
                Output_f->addChild(Set_fraction("1", Input, "0"));
                break;
        }
    }
}

Node * fraction::Set_fraction(const char *numerator, const char *denominator, const char *front){
    float scale = 0.5f;
    for(int i = 0; numerator[i]!=NULL; scale+=0.5f, i++);
    auto fn = (Node *)Node::create(); //最後的回傳-分數的形狀
    Sprite *bar;
    auto Ntor = cocos2d::ui::Text::create();
    auto Dtor = cocos2d::ui::Text::create();
    bar = (Sprite *)Sprite::create("bar.png");
    bar->setScale(6*scale, 5);
    bar->setColor(Color3B::BLACK);
    
    Ntor->setFontSize(60);
    Ntor->setString(numerator);
    Ntor->setPosition(Point(0,30));
    //Ntor->setScale(2.5);
    Ntor->setColor(Color3B::BLACK);
    
    Dtor->setFontSize(60);
    Dtor->setString(denominator);
    Dtor->setPosition(Point(0,-30));
    //Dtor->setScale(2.5);
    Dtor->setColor(Color3B::BLACK);
    
    fn->addChild(bar);
    fn->addChild(Ntor);
    fn->addChild(Dtor);
    
    if(front != "0"){
        auto Ftor = cocos2d::ui::Text::create();
        Ftor->setString(front);
        Ftor->setPosition(Point(-30,0));
        Ftor->setScale(2.5);
        fn->addChild(Ftor);
    }
    return(fn);
}

cocos2d::Node * fraction::FractionOperation(int n){
    char c_n[5];
    sprintf(c_n,"%d",n);
    auto plus = new cocos2d::ui::Text*[n-1]; //加
    auto equal = cocos2d::ui::Text::create(); //等於
    
    auto fn = (Node *)Node::create(); //最後的回傳-運算式的形狀
    
    //分數生成
    Node ** all_f = new Node*[n+1];
    for(int i=0;i<n+1;i++){
        if(i<n)
            all_f[i] = Set_fraction("1", c_n, "0");
        else
            all_f[i] = Set_fraction(c_n, c_n, "0");
    }
    
    //排位子
    for(int i=0; i<2*n+1; i++){
        if(i%2){
            if(i==2*n-1){
                equal = cocos2d::ui::Text::create();
                equal->setString("=");
                //equal->setScale(2.5);
                equal->setFontSize(60);
                equal->setColor(Color3B::BLACK);
                equal->setPosition(Point(50*i,0));
            }
            else{
                plus[(i-1)/2] = cocos2d::ui::Text::create();
                plus[(i-1)/2]->setString("+");
               // plus[(i-1)/2]->setScale(2.5);
                plus[(i-1)/2]->setFontSize(60);
                plus[(i-1)/2]->setColor(Color3B::BLACK);
                plus[(i-1)/2]->setPosition(Point(50*i,0));
            }
        }
        else{
            all_f[i/2]->setPosition(50*i,0);
        }
    }
    
    for(int i=0;i<n+1;i++)
        fn->addChild(all_f[i]);
    for(int i=0;i<n-1;i++)
        fn->addChild(plus[i]);
    fn->addChild(equal);
    
    return(fn);
}

