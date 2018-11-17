#include "faction.h"

void fraction::Input_Que(Node &Q, int number) {
	char Input[5];
	//眔耚
	//瓣
	Text* Output_c = (Text*)Q.getChildByName("C_1");
	Output_c->setString(chiness[number - 2]);
	Output_c->setScale(2);

	//计
	for (int i = 0; i < 2; i++) {
		sprintf(Input, "N_%d", i + 1);
		Text *Output_n = (Text *)Q.getChildByName(Input);
		sprintf(Input, "%d", number);
		Output_n->setString(Input);
		Output_n->setScale(2);
	}

	//だ计
	for (int i = 0; i<3; i++) {
		sprintf(Input, "F_%d", i + 1);
		Node *Output_f = (Node *)Q.getChildByName(Input);
		sprintf(Input, "%d", number);
		if (i < 2)
			Output_f->addChild(Set_fraction("1", Input));
		else
			Output_f->addChild(Set_fraction(Input, Input));
	}

	//笲衡Α
	Node *Output_af = Q.getChildByName("AF_1");
	Output_af->addChild(FractionOperation(number));
}

Node * fraction::Set_fraction(const char *numerator, const char *denominator) {
	auto fn = (Node *)Node::create(); //程肚-だ计
	Sprite *bar;
	auto Ntor = cocos2d::ui::Text::create();
	auto Dtor = cocos2d::ui::Text::create();
	bar = (Sprite *)Sprite::create("bar.png");
	bar->setScale(5, 2);

	Ntor->setString(numerator);
	Ntor->setPosition(Point(0, 15));
	Ntor->setScale(2.5);
	Dtor->setString(denominator);
	Dtor->setPosition(Point(0, -15));
	Dtor->setScale(2.5);

	fn->addChild(bar);
	fn->addChild(Ntor);
	fn->addChild(Dtor);
	return(fn);
}

cocos2d::Node * fraction::FractionOperation(int n) {
	char c_n[5];
	sprintf(c_n, "%d", n);
	auto plus = new cocos2d::ui::Text*[n - 1]; //
	auto equal = cocos2d::ui::Text::create(); //单

	auto fn = (Node *)Node::create(); //程肚-笲衡Α

									  //だ计ネΘ
	Node ** all_f = new Node*[n + 1];
	for (int i = 0; i<n + 1; i++) {
		if (i<n)
			all_f[i] = Set_fraction("1", c_n);
		else
			all_f[i] = Set_fraction(c_n, c_n);
	}

	//逼
	for (int i = 0; i<2 * n + 1; i++) {
		if (i % 2) {
			if (i == 2 * n - 1) {
				equal = cocos2d::ui::Text::create();
				equal->setString("=");
				equal->setScale(2.5);
				equal->setPosition(Point(30 * i, 0));
			}
			else {
				plus[(i - 1) / 2] = cocos2d::ui::Text::create();
				plus[(i - 1) / 2]->setString("+");
				plus[(i - 1) / 2]->setScale(2.5);
				plus[(i - 1) / 2]->setPosition(Point(30 * i, 0));
			}
		}
		else {
			all_f[i / 2]->setPosition(30 * i, 0);
		}
	}

	for (int i = 0; i<n + 1; i++)
		fn->addChild(all_f[i]);
	for (int i = 0; i<n - 1; i++)
		fn->addChild(plus[i]);
	fn->addChild(equal);


	return(fn);
}