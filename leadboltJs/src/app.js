
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        // var mainscene = ccs.load(res.MainScene_json);
        // this.addChild(mainscene.node);

        var coinsLabel = cc.Label.createWithSystemFont("Hello Js", "Arial", 40);
        coinsLabel.setPosition(size.width/2, size.height*9/10);
        this.addChild(coinsLabel);

        cc.MenuItemFont.setFontName('arial');
        cc.MenuItemFont.setFontSize(32);

        var menu = new cc.Menu(
            new cc.MenuItemFont("cache", function () {
                sdkbox.PluginLeadBolt.loadModuleToCache("ad1");
            }, this),
            new cc.MenuItemFont("show", function () {
                if (sdkbox.PluginLeadBolt.isAdReady("ad1")) {
                    sdkbox.PluginLeadBolt.loadModule("ad1");
                } else {
                    console.log("ad is not ready")
                }
            }, this)
            );
        menu.setPosition(size.width/2, size.height/2);
        menu.alignItemsVerticallyWithPadding(20);
        this.addChild(menu);

        var initSDK = function() {
            if ("undefined" == typeof(sdkbox)) {
                console.log("sdkbox is not exist")
                return
            }

            if ("undefined" != typeof(sdkbox.PluginLeadBolt)) {
                var plugin = sdkbox.PluginLeadBolt
                plugin.setListener({
                  onModuleLoaded: function(placement) {
                    console.log("onModuleLoaded:" + placement)
                  },
                  onModuleClosed: function(placement) {
                    console.log("onModuleClosed:" + placement)
                  },
                  onModuleClicked: function(placement) {
                    console.log("onModuleClicked:" + placement)
                  },
                  onModuleCached: function(placement) {
                    console.log("onModuleCached:" + placement)
                  },
                  onModuleFailed: function(placement, error, cached) {
                    console.log("onModuleFailed:" + placement + " error:" + error + " cached:" + cached)
                  },
                  onMediaFinished: function(viewCompleted) {
                    console.log("onMediaFinished:" + viewCompleted)
                  }
                })
                plugin.init()
            } else {
                console.log("no plugin init")
            }
        }

        initSDK();

        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

