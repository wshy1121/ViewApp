#include "ListViewLayer.h"
#include "InTraceLayer.h"
#include "VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* ListViewLayer::createScene()
{
	Scene* sc			=	Scene::create();
	ListViewLayer* ly	=	ListViewLayer::create();
	sc->addChild(ly);

	return sc;
}
bool ListViewLayer::init()
{	trace_worker();
	m_cellNum = 9;
	initTableCellVec();	
	CCLayer::init();

	CNetClient::instance()->getTraceFileList(m_fileList);

	Sprite *pSprite = Sprite::createWithSpriteFrameName("background_2.png");
	pSprite->setPosition((Vec2::ZERO));
	pSprite->setAnchorPoint((Vec2::ZERO));
	this->addChild(pSprite);

	m_tableView = TableView::create(this, CCSizeMake(320, 568));
	m_tableView->setDirection(ScrollView::Direction::VERTICAL);
	m_tableView->setPosition((Vec2::ZERO));
	m_tableView->setDelegate(this);
	m_tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(m_tableView);
	m_tableView->reloadData();
	
	updateListView(0);
	addEvents();
	return true;
}



void ListViewLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{	trace_worker();
	trace_printf("cell touched at index: %i", cell->getIdx());
	trace_printf("m_touchPoint.x, m_touchPoint.y  %f  %f", m_touchPoint.x, m_touchPoint.y);

	CCLabelTTF *pLabel = (CCLabelTTF*)cell->getChildByTag(e_tableCellDelete);
	Vec2 node = pLabel->convertToNodeSpace(m_touchPoint);
	trace_printf("node.x, node.y  %f  %f", node.x, node.y);
	Size lableSize = pLabel->getContentSize();
	trace_printf("lableSize.width, lableSize.height  %f  %f", lableSize.width, lableSize.height);
	
	if (cell->getIdx() >= m_fileList.size())
	{
		return ;
	}
	
	TraceFileInf &traceFileInf = m_fileList[cell->getIdx()];	
	if (isNodeInSize(lableSize, node))
	{	trace_printf("NULL");
		CNetClient::instance()->cleanFile(traceFileInf.m_fileName.c_str());
		updateListView(0);
		return ;
	}	
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,InTraceLayer::createScene(traceFileInf.m_fileName.c_str()),true));
}

CCSize ListViewLayer::cellSizeForTable(TableView *table)
{	trace_worker();
    return CCSizeMake(320, 60);
}

void ListViewLayer::formatTraceFileInf(int index, TraceFileInf &traceFileInf, char *data, int dataLen)
{	trace_worker();
	char units[4] = {' ', 'K', 'M', 'G'};
	size_t &fileSize = traceFileInf.m_fileSize;
	int reMainSize = 0;
	int unitsIndex = 0;
	while (1)
	{
		if ((traceFileInf.m_fileSize >> 10) == 0)
		{
			break;
		}
		++unitsIndex;
		reMainSize = (traceFileInf.m_fileSize % 1024) * 100 >> 10;
		fileSize = traceFileInf.m_fileSize >> 10;
	}
	snprintf(data, dataLen, "%d  %s  %d.%02d%c", index, traceFileInf.m_fileName.c_str(), traceFileInf.m_fileSize, reMainSize, units[unitsIndex]);
	return ;
}

TableViewCell *ListViewLayer::createTableCell()
{	trace_worker();
	TableViewCell *pCell = NULL;
	trace_printf("NULL");
	pCell = new TableViewCell();
	trace_printf("NULL");
	pCell->autorelease();
	trace_printf("NULL");
	CCSprite *pSprite = CCSprite::create("listitem.png");
	pSprite->setAnchorPoint((Vec2::ZERO));
	pSprite->setPosition((Vec2::ZERO));
	pCell->addChild(pSprite);
	trace_printf("NULL");
	CCLabelTTF *pLabel = CCLabelTTF::create("", "Arial", 20.0);
	pLabel->setPosition((Vec2::ZERO) + Vec2(0, 20));
	pLabel->setAnchorPoint((Vec2::ZERO));
	pLabel->setTag(e_tableCellInf);
	pCell->addChild(pLabel);
	trace_printf("NULL");	

	int diffX = VisibleRect::getVisibleRect().getMaxX()-32;
	pLabel = CCLabelTTF::create("", "Arial", 20.0);
	pLabel->setContentSize(Size(64, 57));
	pLabel->setPosition((Vec2::ZERO) + Vec2(diffX, 20));
	pLabel->setAnchorPoint((Vec2::ZERO));
	pLabel->setTag(e_tableCellDelete);
	pCell->addChild(pLabel);
	return pCell;
}
void ListViewLayer::initTableCellVec()
{	trace_worker();
	TableViewCell *pCell = NULL;
	for (int i=0; i<m_cellNum; ++i)
	{
		pCell = createTableCell();
		m_tableCellVec.pushBack(pCell);
	}
	return ;
}

TableViewCell* ListViewLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{	trace_worker();
	trace_printf("idx  %d", idx);

	return m_tableCellVec.at(idx);
}

ssize_t ListViewLayer::numberOfCellsInTableView(TableView *table)
{	trace_worker();
    return m_cellNum;
}


void ListViewLayer::scrollViewDidScroll(ScrollView *view)
{	trace_worker();
}

void ListViewLayer::scrollViewDidZoom(ScrollView *view)
{	trace_worker();
}

void ListViewLayer::updateListView(float dt)
{	trace_worker();
	int oldFileListSize = m_fileList.size();
	
	m_fileList.clear();
	CNetClient::instance()->getTraceFileList(m_fileList);

	TableViewCell *pCell = NULL;
	CCLabelTTF *pLabel = NULL;
	char strText[256];
	for (int i=0; i<m_fileList.size(); ++i)
	{	trace_printf("index  %d", i);
		pCell = m_tableCellVec.at(i);
		formatTraceFileInf(i, m_fileList[i], strText, sizeof(strText));
		trace_printf("NULL");
		pLabel = (CCLabelTTF*)pCell->getChildByTag(e_tableCellInf);
        pLabel->setString(strText);
		pLabel = (CCLabelTTF*)pCell->getChildByTag(e_tableCellDelete);
		pLabel->setString("Del");
		trace_printf("strText  %s", strText);
	}
	
	for (int i=m_fileList.size(); i<oldFileListSize; ++i)
	{
		pCell = m_tableCellVec.at(i);
		pLabel = (CCLabelTTF*)pCell->getChildByTag(e_tableCellInf);
		pLabel->setString("");
		pLabel = (CCLabelTTF*)pCell->getChildByTag(e_tableCellDelete);
		pLabel->setString("");
	}
	

}

void ListViewLayer::onEnterTransitionDidFinish()
{	trace_worker();
	Layer::onEnterTransitionDidFinish();
	this->schedule(SEL_SCHEDULE(&ListViewLayer::updateListView), 1.0f);
}

bool ListViewLayer::isNodeInSize(Size &size, Vec2 &node)
{	trace_worker();
	if (0 < node.x && node.x < size.width && 0 < node.y && node.y < size.height)
	{	trace_printf("true");
		return true;
	}
	trace_printf("false");
	return false;
}

void ListViewLayer::addEvents()
{
	auto touchEvt = EventListenerTouchOneByOne::create();
	touchEvt->onTouchBegan = CC_CALLBACK_2(ListViewLayer::onTouchBegan, this);
	touchEvt->onTouchMoved = CC_CALLBACK_2(ListViewLayer::onTouchMoved, this);
	touchEvt->onTouchEnded = CC_CALLBACK_2(ListViewLayer::onTouchEnded, this);
	touchEvt->onTouchCancelled = CC_CALLBACK_2(ListViewLayer::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt, this);
}

bool ListViewLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{	trace_worker();
	m_touchPoint = touch->getLocation();
	return true;
}

void ListViewLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void ListViewLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{	trace_worker();


}
void ListViewLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{	trace_worker();

}

