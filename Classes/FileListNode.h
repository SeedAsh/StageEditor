#ifndef __FILELISTNODE_H__
#define __FILELISTNODE_H__
#include "cocos2d.h"
#include "TouchNode.h"

class FileListNode
	: public cocos2d::CCNode
{
public:
	static FileListNode *create(const std::string &fileName);
	void setBkVisible(bool isVisible);
	std::string getFileName(){ return m_fileName; }
private:
	virtual bool init();

	FileListNode(const std::string &fileName) : m_fileName(fileName){}
private:
	std::string m_fileName;
	cocos2d::CCLabelTTF *m_label;
	CCNode *m_bk;
};
#endif