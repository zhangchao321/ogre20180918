#ifndef CUBE_SAMPLE_H
#define CUBE_SAMPLE_H

#include "SdkSample.h"
#include "OgreManualObject.h"

class _OgreSampleClassExport CubeSample :public OgreBites::SdkSample
{
public:
	CubeSample();

protected:
	void setupContent() override;
	void cleanupContent() override; 
	bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

private:
	void setUpScene();

private: 
	Ogre::ManualObject* manualObject;
};

//////////////////////////////////////////////////////////////////////////
CubeSample::CubeSample()
{

	mInfo["Title"] = "SimpleCube";
	mInfo["Description"] = "A demonstration of ogre's cube";
	mInfo["Thumbnail"] = "cube.png";
	mInfo["Category"] = "SimpleGeometry";
}

void CubeSample::setupContent()
{
	// set our camera to orbit around the origin and show cursor
	mCameraMan->setStyle(CS_ORBIT);
	mTrayMgr->showCursor();
	setUpScene();
}

void CubeSample::cleanupContent()
{
	SdkSample::cleanupContent();
}

bool CubeSample::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return SdkSample::frameRenderingQueued(evt);
}

void CubeSample::setUpScene()
{
	manualObject = mSceneMgr->createManualObject("mo");
	manualObject->begin("BaseWhiteNoLighting");

	Ogre::Real cm = -5.0;
	Ogre::Real cp = 5.0;

	manualObject->position(cm, cp, cm);// a vertex
	manualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f));
	manualObject->position(cp, cp, cm);// a vertex
	manualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 0.0f, 1.0f));
	manualObject->position(cp, cm, cm);// a vertex
	manualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f));
	manualObject->position(cm, cm, cm);// a vertex
	manualObject->colour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));

	manualObject->position(cm, cp, cp);// a vertex
	manualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 1.0f, 1.0f));
	manualObject->position(cp, cp, cp);// a vertex
	manualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
	manualObject->position(cp, cm, cp);// a vertex
	manualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 1.0f, 1.0f));
	manualObject->position(cm, cm, cp);// a vertex
	manualObject->colour(Ogre::ColourValue(0.0f, 0.0f, 1.0f, 1.0f));

	// face behind / front
	manualObject->triangle(0, 1, 2);
	manualObject->triangle(2, 3, 0);
	manualObject->triangle(4, 6, 5);
	manualObject->triangle(6, 4, 7);

	// face top / down
	manualObject->triangle(0, 4, 5);
	manualObject->triangle(5, 1, 0);
	manualObject->triangle(2, 6, 7);
	manualObject->triangle(7, 3, 2);

	// face left / right
	manualObject->triangle(0, 7, 4);
	manualObject->triangle(7, 0, 3);
	manualObject->triangle(1, 5, 6);
	manualObject->triangle(6, 2, 1);

	manualObject->end();


	Ogre::String lNameOfTheMesh = "MeshCubeAndAxe";
	manualObject->convertToMesh(lNameOfTheMesh);

	Ogre::Entity* entity = mSceneMgr->createEntity(lNameOfTheMesh);

	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entity);
}
#endif // !CUBE_SAMPLE_H