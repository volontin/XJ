//
//  CusorTextField.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-16.
//
//

#include "CursorTextField.h"
#include "support/CCNotificationCenter.h"

static int _calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

const static float DELTA = 20.0f;

CursorTextField::CursorTextField()
{
    CCTextFieldTTF();
    
    m_pCursorSprite = NULL;
    m_pCursorAction = NULL;
    
    m_pInputText = NULL;
    isPsw = false;
    m_limitNum = 30;
}

CursorTextField::~CursorTextField()
{
    CC_SAFE_DELETE(m_pCursorSprite);
    CC_SAFE_DELETE(m_pCursorAction);
    CC_SAFE_DELETE(m_pInputText);
}

void CursorTextField::onEnter()
{
    CCTextFieldTTF::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, false);
    this->setDelegate(this);
}
//静态生成函数
CursorTextField * CursorTextField::textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    CursorTextField *pRet = new CursorTextField();
    
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        pRet->initCursorSprite(fontSize);
        pRet->m_pCursorSprite->setVisible(false);
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    
    return NULL;
}

CursorTextField * CursorTextField::textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    CursorTextField *pRet =  CursorTextField::textFieldWithPlaceHolder(placeholder,fontName,fontSize);
    if(pRet)
        return pRet;
    
    CC_SAFE_DELETE(pRet);
    
    return NULL;
}
void CursorTextField::initCursorSprite(int nHeight)
{
    // 初始化光标
    int column = 4;
    int pixels[nHeight][column];
    for (int i=0; i<nHeight; ++i) {
        for (int j=0; j<column; ++j) {
            pixels[i][j] = 0xffffffff;
        }
    }
    
    CCTexture2D *texture = new CCTexture2D();
    texture->initWithData(pixels, kCCTexture2DPixelFormat_RGB888, 1, 1, CCSizeMake(column, nHeight));
    
    m_pCursorSprite = CCSprite::createWithTexture(texture);
    m_cursorPos = ccp(1, getContentSize().height / 2);
    m_pCursorSprite->setPosition(m_cursorPos);
    this->addChild(m_pCursorSprite);
    
    m_pCursorAction = CCRepeatForever::create((CCActionInterval *) CCSequence::create(CCFadeOut::create(0.25f), CCFadeIn::create(0.25f), NULL));
    
    m_pCursorSprite->runAction(m_pCursorAction);
    
    m_pInputText = new std::string();
}

bool CursorTextField::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_beginPos = pTouch->getLocationInView();
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
    
    return true;
}

CCRect CursorTextField::getRect()
{
    CCSize size;
    if (&m_designedSize != NULL) {
        size = getDesignedSize();
    }else {
        size = getContentSize();
    }

    CCRect rect = CCRectMake(getPosition().x-size.width/2.0f, getPosition().y-size.height/2.0f, size.width, size.height);
    return  rect;
}
//设置触摸弹出输入法的区域大小
void CursorTextField::setDesignedSize(cocos2d::CCSize size)
{
    m_designedSize = size;
    m_limitRow = static_cast<int>(size.height/getFontSize());
    if (m_limitRow==1) {
        
    }
}

CCSize CursorTextField::getDesignedSize()
{
    return m_designedSize;
}

bool CursorTextField::isInTextField(cocos2d::CCTouch *pTouch)
{
     CCPoint pToushPos = pTouch->getLocation();
    return getRect().containsPoint(pToushPos);
}

void CursorTextField::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint endPos = pTouch->getLocationInView();
    
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);
    // 判断是否为点击事件
    if (::abs(endPos.x - m_beginPos.x) > DELTA ||
        ::abs(endPos.y - m_beginPos.y) > DELTA)
    {
        // 不是点击事件
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }
    
    // 判断是打开输入法还是关闭输入法
    isInTextField(pTouch) ? openIME() : closeIME();
}

bool CursorTextField::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *pSender)
{
    if (m_pInputText->empty()) {
        return false;
    }
    
    m_pCursorSprite->setPosition(ccp(getContentSize().width+1,getContentSize().height/2));
    
    return false;
}

bool CursorTextField::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
{
//    CCLOG("Width: %f", pSender->getContentSize().width);
//    CCLOG("Text: %s", text);
//    CCLOG("Length: %d", nLen);
    CCString * str = CCString::create(text);
    if(str->isEqual(new CCString("\n"))){
        closeIME();
        return false;
    }
//    else if(str->isEqual(new CCString(" "))){
//    }
    std::string tempStr = m_pInputText->substr();
    tempStr.append(text);
    if (tempStr.length() > m_limitNum) {
        return true;
    }
    
    m_pInputText->append(text);
    
    if (isPsw) {
        std::string tempStr;
        for (int i = 0; i < m_pInputText->size(); i++) {
            tempStr.append("*");
        }
        setString(tempStr.c_str(), m_pInputText->c_str());
    }else {

        setString(m_pInputText->c_str(), m_pInputText->c_str());
    }
    
    m_pCursorSprite->setPosition(ccp(getContentSize().width+1,getContentSize().height/2));
    
    return true;
}

bool CursorTextField::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen)
{
    m_pInputText->resize(m_pInputText->size() - nLen);
//    CCLog(m_pInputText->c_str());
    
    if (isPsw) {
        std::string tempStr;
        for (int i = 0; i < m_pInputText->size(); i++) {
            tempStr.append("*");
        }
        setString(tempStr.c_str(), m_pInputText->c_str());
    }else {
        setString(m_pInputText->c_str(), m_pInputText->c_str());
    }
    
    m_pCursorSprite->setPosition(ccp(getContentSize().width+1,getContentSize().height/2));
    
    if (m_pInputText->empty()) {
        m_pCursorSprite->setPosition(ccp(1,getContentSize().height/2));
    }
    
    return true;
}

bool CursorTextField::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *pSender)
{
    return false;
}

void CursorTextField::openIME()
{
    m_pCursorSprite->setVisible(true);
    this->attachWithIME();
}

void CursorTextField::closeIME()
{
    m_pCursorSprite->setVisible(false);
    this->detachWithIME();
}

void CursorTextField::onExit()
{
    this->detachWithIME();
    CCTextFieldTTF::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool CursorTextField::getIsPsw()
{
    return isPsw;
}
//设置星号显示否
void CursorTextField::setIsPsw( bool bFlag)
{
    isPsw = bFlag;
}

int CursorTextField::getLimitNum()
{
    return m_limitNum;
}
//设置字符长度
void CursorTextField::setLimitNum(int limitNum)
{
    m_limitNum = limitNum;
}

void CursorTextField::setString(const char *displayTx, const char* inputTx)
{
    CC_SAFE_DELETE(m_pInputText);
    
    if (inputTx)
    {
        m_pInputText = new std::string(inputTx);
    }
    else
    {
        m_pInputText = new std::string;
    }
    
    // if there is no input text, display placeholder instead
    if (! m_pInputText->length())
    {
        CCLabelTTF::setString(m_pPlaceHolder->c_str());
    }
    else
    {
        CCLabelTTF::setString(displayTx);
    }
//    m_nCharCount = _calcCharCount(m_pInputText->c_str());
}

void CursorTextField::setColor(const ccColor3B& color3)
{
    updateColor();
    m_pCursorSprite->setColor(color3);
}