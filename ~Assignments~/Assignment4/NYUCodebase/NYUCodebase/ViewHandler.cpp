#include "ViewHandler.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <algorithm>

using namespace std;

ViewHandler::ViewHandler(ShaderProgram** programhandle)
	: programhandle(programhandle)
{
}

bool ViewHandler::setActiveView(Camera* const camera)
{
	if(views.insert(camera).second)
	{
		viewHist.push_back(camera);
		return true;
	}
	return false;
}

pair<const list<Camera*>::const_iterator&, bool> ViewHandler::forceActiveView(Camera* const camera)
{
	if(setActiveView(camera)) return pair<list<Camera*>::const_iterator, bool>(std::prev(viewHist.end()), true);
	list<Camera*>::const_iterator i = find(viewHist.begin(), viewHist.end(), camera);
	viewHist.splice(viewHist.end(), viewHist, i);
	return pair<list<Camera*>::const_iterator, bool>(i, false);
}

const Camera& ViewHandler::activeView() const
{
	return *(viewHist.back());
}

int ViewHandler::inactivity(Camera* const camera) const
{
	if(views.find(camera) == views.end()) return -1;
	return distance(find(viewHist.begin(), viewHist.end(), camera), std::prev(viewHist.end()));
}

const Camera& ViewHandler::revertView()
{
	Camera* camera = *viewHist.erase(std::prev(viewHist.end()));
	views.erase(camera);
	return *camera;
}

list<Camera*>::const_iterator ViewHandler::removeView(Camera* const camera)
{
	views.erase(camera);
	return viewHist.erase(find(viewHist.begin(), viewHist.end(), camera));
}

void ViewHandler::operator()()
{
	program()->setViewMatrix(activeView().getViewMatrix());
	program()->setProjectionMatrix(activeView().getProjectionMatrix());
}

ShaderProgram*& ViewHandler::program() const
{
	return *programhandle;
}

ViewHandler handleViews;

ShaderProgram** const ViewHandler::defaultProgram = &::program;