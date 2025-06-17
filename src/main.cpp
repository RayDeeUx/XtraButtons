#include <alphalaneous.pages_api/include/PageMenu.h>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;
		if (!Utils::modEnabled() || !Utils::getBool("hallOfFame") || p0) return true;

		const auto &quickSearchMenu = getChildByIDRecursive("quick-search-menu");
		if (!quickSearchMenu) return true;

		const auto &hallOfFameButtonSprite = SearchButton::create("GJ_longBtn04_001.png", "Hall of Fame", .5f, "hallOfFame.png"_spr);
		hallOfFameButtonSprite->setID("hall-of-fame-sprite"_spr);
		const auto &label = hallOfFameButtonSprite->m_label;
		const auto &icon = hallOfFameButtonSprite->m_icon;
		label->setPositionX(label->getPositionX() + 5.f);
		icon->setPositionX(icon->getPositionX() - 15.f);
		label->setID("hall-of-fame-label"_spr);
		icon->setID("hall-of-fame-icon"_spr);
		label->setScale(.35f);
		icon->setScale(.4f);

		const auto &hallOfFameTabButton = CCMenuItemSpriteExtra::create(hallOfFameButtonSprite, this, menu_selector(MyLevelSearchLayer::onHallOfFame));
		hallOfFameTabButton->setID("hall-of-fame-button"_spr);

		RowLayout* layout = RowLayout::create();
		layout->setGrowCrossAxis(true)->setCrossAxisOverflow(false)->setAxisAlignment(AxisAlignment::Center)->setCrossAxisAlignment(AxisAlignment::Center)->ignoreInvisibleChildren(true);

		quickSearchMenu->setContentSize({365, 116});
		quickSearchMenu->ignoreAnchorPointForPosition(false);
		quickSearchMenu->setPosition({quickSearchMenu->getPosition().x, (CCDirector::get()->getWinSize().height / 2.f) + 28});
		quickSearchMenu->setLayout(layout);
		quickSearchMenu->addChild(hallOfFameTabButton);

		static_cast<PageMenu*>(quickSearchMenu)->setPaged(9, PageOrientation::HORIZONTAL, 422);

		return true;
	}

	void onHallOfFame(CCObject* sender) {
		if (!Utils::modEnabled()) return;
		const auto &scene = CCScene::create();
		scene->addChild(LevelBrowserLayer::create(GJSearchObject::create(SearchType::HallOfFame)));
		CCDirector::get()->pushScene(CCTransitionFade::create(.5f, scene));
	}
};

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		if (!Utils::modEnabled() || !Utils::getBool("moreGames")) return true;

		CCLabelBMFont* moreGamesLabel = CCLabelBMFont::create("More\nGames", "goldFont.fnt");
		moreGamesLabel->setAlignment(kCCTextAlignmentCenter);
		CircleButtonSprite* moreGamesSprite = CircleButtonSprite::create(moreGamesLabel, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
		CCMenuItemSpriteExtra* moreGamesButton = CCMenuItemSpriteExtra::create(moreGamesSprite, this, menu_selector(MenuLayer::onMoreGames));
		moreGamesButton->setID("more-games-button"_spr);
		CCNode* bottomMenu = this->getChildByID("bottom-menu");
		if (!bottomMenu) return true;
		bottomMenu->addChild(moreGamesButton);
		bottomMenu->updateLayout();

		return true;
	}
};