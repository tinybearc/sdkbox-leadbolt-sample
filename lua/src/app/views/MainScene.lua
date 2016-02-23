
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

-- MainScene.RESOURCE_FILENAME = "MainScene.csb"

function MainScene:onCreate()
    -- printf("resource node = %s", tostring(self:getResourceNode()))
    cc.MenuItemFont:setFontName("Arial")
    cc.Menu:create(
                   cc.MenuItemFont:create("cache"):onClicked(function()
                        print("cache click")
                        self:cacheInterstitial()
                    end),
                   cc.MenuItemFont:create("show"):onClicked(function()
                        print("show click")
                        self:showInterstitial()
                    end)
                   )
        :move(display.cx, display.cy)
        :addTo(self)
        :alignItemsVerticallyWithPadding(20)

    cc.Label:createWithSystemFont("Hello Lua", "Arial", 40)
            :move(display.cx, display.height*9/10)
            :addTo(self)

    self:initSDK()
end

function MainScene:initSDK()
    if not sdkbox then
        print "sdkbox is nil"
        return
    end

    print "Entry initSDK"

    if sdkbox.PluginLeadBolt then
        local plugin = sdkbox.PluginLeadBolt
        plugin:setListener(function(args)
            local event = args.event
            dump(args, "leadbolt listener info:")
        end)
        plugin:init()

    else
        print "not found plugin"
    end
end

function MainScene:showInterstitial()
    if not sdkbox then
        print "sdkbox is nil"
        return
    end

    print "Entry showInterstitial"

    if sdkbox.PluginLeadBolt then
        local plugin = sdkbox.PluginLeadBolt
        if plugin:isAdReady('ad1') then
            plugin:loadModule('ad1')
        else
            print('leadbolt ad is not ready')
        end
    else
        print "not found plugin"
    end
end

function MainScene:cacheInterstitial()
    if not sdkbox then
        print "sdkbox is nil"
        return
    end

    print "Entry cacheInterstitial"

    if sdkbox.PluginLeadBolt then
        local plugin = sdkbox.PluginLeadBolt
        plugin:loadModuleToCache('ad1')
    else
        print "not found plugin"
    end
end

return MainScene
