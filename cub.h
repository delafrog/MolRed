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
	vec3db rc; // ���������� ������ ��������������
	vec3db abc; // ������� ��������������
	Quaternion<double> q; // ���������� �������� ��������������.
}