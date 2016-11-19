#pragma once
#include "Matrix.h"
#include <unordered_set>
#include <list>

class ShaderProgram;
class Camera;

class ViewHandler
{
public:
	ViewHandler(ShaderProgram** = defaultProgram);

	bool setActiveView(Camera* const);
	std::pair<const std::list<Camera*>::const_iterator&, bool> forceActiveView(Camera* const);
	const Camera& activeView() const;
	int inactivity(Camera* const) const;
	const Camera& revertView();
	std::list<Camera*>::const_iterator removeView(Camera* const);
	void operator()();

private:
	ShaderProgram*& program() const;
	
	std::unordered_set<Camera*> views;
	std::list<Camera*> viewHist;

	ShaderProgram** programhandle;
	static ShaderProgram** const defaultProgram;
};

extern ViewHandler handleViews;