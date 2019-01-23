#include "sceneTest1.h"

#include "managerList.h"

#include "labelBase.h"

void sceneTest1::init(void)
{
	sceneBase::init();

	_stackTime = 0.0f;
}

void sceneTest1::update(void)
{
	sceneBase::update();

	_stackTime += MN_TIME->getDeltaTime();

	updateControl();
}

void sceneTest1::draw(void)
{
	sceneBase::draw();
}

void sceneTest1::drawUI(void)
{
	sceneBase::drawUI();

	char text[MAX_PATH] = "";

	sprintf(text, "\n\n\n\nscene : sceneTest1\ncurrentValue : %f", _stackTime);

	_label->setText(text);
	_label->drawUI();
}

void sceneTest1::updateControl(void)
{
	if (MN_KEY->keyPress(DIK_1)) MN_SCENE->change("scene1");
	if (MN_KEY->keyPress(DIK_2)) MN_SCENE->change("scene2");
}
