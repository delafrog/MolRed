#ifndef CUB_H
#define CUB_H

#include <QWidget>
#include "linalg.h"
#include "linalg.cpp"
#include "rdwrfls.h"
#include "GLframe.h"
//class QObject;
//class WorkFrame;


class UserSpace:: public QWidget
{
public:
	vec3db rc; // координаты центра паралелипипеда
	vec3db abc; // стороны паралелипипеда
	Quaternion<double> q; // кватернион поворота паралелипипеда.
}