#include "FileListNode.h"
#include "StarsHelper.h"
#include "EditorModel.h"
#include "Util.h"
USING_NS_CC;
using namespace std;

FileListNode *FileListNode::create(const std::string &fileName)
{
	FileListNode *node = new FileListNode(fileName);
	node->init();
	node->autorelease();
	return node;
}

bool FileListNode::init()
{
	m_label = CCLabelTTF::create(m_fileName.c_str(), "Arial", 24);
	m_label->setString(m_fileName.c_str());
	auto size = m_label->getContentSize();
	size.width += 50;
	m_label->setAnchorPoint(ccp(0, 0.5f));
	m_label->setPosition(ccp(0, size.height * 0.5f));
	addChild(m_label, 1);

	m_bk = getMask(size, ccc4(0, 0, 255, 175));
	addChild(m_bk);
	m_bk->setVisible(false);

	setContentSize(size);
	return true;
}

void FileListNode::setBkVisible(bool isVisible)
{
	m_bk->setVisible(isVisible);
}
