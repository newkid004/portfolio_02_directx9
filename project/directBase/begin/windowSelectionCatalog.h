#pragma once
#include "kGlobalDefine.h"
#include "windowSelection.h"

template<typename T>
class windowMvCatalog;

// ----- selection ----- //
template<typename T>
class windowSelectionCatalog : public windowSelection
{
protected :
	void initBind(void) override;

public:
	windowSelectionCatalog(const uiInfo & info, windowMvCatalog<T>* bindWindow) : windowSelection(info, bindWindow) {};
	virtual ~windowSelectionCatalog() {};
};

#include "windowSelectionCatalog.hpp"
