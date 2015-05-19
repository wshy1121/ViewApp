#ifndef __TABLEVIEWTESTSCENE_H__
#define __TABLEVIEWTESTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "trace_worker.h"
#include "net_client.h"

class ListViewLayer : public cocos2d::CCLayer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	typedef enum
	{
		e_tableCellInf = 123,
		e_tableCellDelete,
	};
	static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ListViewLayer);	
private:
	virtual void onEnterTransitionDidFinish();
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
	//�������¼�
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	//ÿһ��Ŀ�Ⱥ͸߶�
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::TableView *table);
	//�����б�ÿһ�������
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	//һ��������
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	void updateListView(float dt);
	void formatTraceFileInf(int index, TraceFileInf &traceFileInf, char *data, int dataLen);
	void initTableCellVec();
	cocos2d::extension::TableViewCell *createTableCell();	
	bool isNodeInSize(cocos2d::Size &size, cocos2d::Vec2 &node);
	void addEvents();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);		
private:
	typedef cocos2d::Vector<cocos2d::extension::TableViewCell *> TableCellVec;
	cocos2d::Point m_touchPoint;
	cocos2d::extension::TableView* m_tableView;
	CTraceClient::TraceFileVec m_fileList;
	TableCellVec m_tableCellVec;
	int m_cellNum;
};

#endif 
