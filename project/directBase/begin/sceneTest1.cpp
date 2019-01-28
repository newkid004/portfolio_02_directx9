#include "sceneTest1.h"

#include "managerList.h"

#include "labelBase.h"
#include "gJson.h"

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

	if (MN_KEY->mousePress())
	{
		for (int i = 0 ; i <= _count; ++i)
			_json["count" + to_string(_save)][_count][i] = i * _count;

		++_count;
	}
	if (MN_KEY->mousePress(EMouseInput::RIGHT))
	{
		gJson::write(_json, "test.json");
		++_save;
	}
	if (MN_KEY->mousePress(EMouseInput::MIDDLE))
	{
		gJson::read(_json, "test.json");
		for (auto j : _json["count0"])
		{
			for (auto jin : j)
			{
				int getter;
				jin.get_to<int>(getter);

				printf("%d ", getter);
			}
			printf("\n");
		}
	}
}
