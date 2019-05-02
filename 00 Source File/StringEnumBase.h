/**
* @file StringEnumBase.h
* @brief �����񂩂�ϊ��ł���񋓌^�𓮓I�ɐ���
* @author Ryunosuke Honda.
*/
#pragma once

#include <unordered_map>
#include <string>
#include <stdarg.h>
#include <string.h>

/**
* @def ENUM
* string����ϊ��ł���enum�̐������s��
*/
#define ENUM(_name, ...)												\
	struct _name {														\
		enum type : unsigned int{__VA_ARGS__, NUM};									\
		unordered_map<string, type> converter;				\
		_name() {														\
			createEnumMap(converter, #__VA_ARGS__, NUM, __VA_ARGS__);	\
		}																\
	}_name;

/**
*	�񋓎q��������������L�[�Ƃ��񋓒萔�̐��l��l�Ƃ���map���쐬����
*/
template <class T>
void createEnumMap(unordered_map<string, T> &_map, char* _list, int _num, ...)
{
	char* listCopy = new char[255];
	char* tmpKey;
	strcpy_s(listCopy, 255, _list);

	va_list args;
	va_start(args, _num);

	char *p;
	if ((tmpKey = strtok_s(listCopy, ", ", &p)) != NULL) _map[tmpKey] = static_cast<T>(va_arg(args, int));
	for (int i = 0; i < _num; i++) {
		if ((tmpKey = strtok_s(NULL, ", ", &p)) != NULL) _map[tmpKey] = static_cast<T>(va_arg(args, int));
	}
	va_end(args);
	delete[] listCopy;
}

/****** End of File *****************************************************/
