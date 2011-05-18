function ebCBrowserDetector(browserType,browserVer,platform){var browserTypes={notsupported:0,ie:1,ff:2,nn:3,safari:4,chrome:5,aol:6,opera:7};var platformTypes={notsupported:0,win95:1,win98:2,win2k:3,winXP:4,winME:5,winNT:6,Mac:7,winVista:8,win7:9};this.browserType=browserType;this.browserVer=browserVer;this.platform=platform;this.getVersion=function(){return this.browserVer;};this.isIE=function(){return this.browserType==browserTypes.ie||this.browserType==browserTypes.aol;};this.isFF=function(){return this.browserType==browserTypes.ff;};this.isSafari=function(){return this.browserType==browserTypes.safari||this.browserType==browserTypes.chrome;};this.isRealSafari=function(){return this.browserType==browserTypes.safari;};this.isChrome=function(){return this.browserType==browserTypes.chrome;};this.isNN=function(){return this.browserType==browserTypes.nn;};this.isAOL=function (){return this.browserType==browserTypes.aol;};this.isOpera=function (){return this.browserType==browserTypes.opera;};this.isMac=function(){return this.platform==platformTypes.Mac;};}if(typeof(gEbBC)=="undefined")gEbBC=new ebCBrowserDetector(ebO.bt,ebO.bv,ebO.plt);function ebGetVersionToReport(adData){var version=(adData.sAdVersions.indexOf(",")>-1)?gEbSV2Constant:adData.sAdVersions;return version;}function ebGetTargetingParams(adData){var params="";if(adData.sTAId)params+=ebFormat("&ta={0}",adData.sTAId);if(adData.sDGId)params+=ebFormat("&dg={0}",adData.sDGId);return params;}function ebFormat(str){for(i=1;i<arguments.length;i++){str=str.replace('{' + (i-1) + '}', ""+arguments[i]);}return str;}if(typeof(gEbnIntSeqArray)=="undefined"&&gEbBC.isOpera())gEbnIntSeqArray=new Array(5,10,20,40,60,120,240);function ebReportTimersInterval(){if(typeof(gEbBanners)!="undefined")ebReportInteractions(gEbBanners);if(typeof(gEbEyes)!="undefined")ebReportInteractions(gEbEyes);if(typeof(gEbStdBanners)!="undefined")ebReportInteractionsStd();gEbnIntSeq++;if(typeof(gEbnIntSeqArray[gEbnIntSeq])!="undefined")window.setTimeout("ebReportTimersInterval()",gEbnIntSeqArray[gEbnIntSeq]*1000);}function ebIsGlobalDef(varName,varValue){var typeofVar =eval("typeof(" + varName + ")");var isDefined=(typeofVar !="undefined");if((typeof(varValue)!="undefined")&&isDefined){isDefined=eval(varName+"=="+varValue);}return isDefined;}var gEbSV2Constant="m";if(typeof(gEbFlyLocal)=="undefined")gEbFlyLocal=false;ebBS=unescape(ebO.bs);ebIntTimeVer=gEbFlyLocal?"" : "V62_12";ebConduitVer=gEbFlyLocal?"" : "54";ebBigS=unescape(ebO.bgs);ebResourcePath=unescape(ebO.rp);ebPluID=ebO.pi;var ebStrProtocol=ebResourcePath.substr(0,ebResourcePath.indexOf(":")+3);var gEBvideoTypes={"WMV":0,"FLV8":1,"FLV7":2,"SWF":3,"MP4":4,"F4V":5};function ebCStdBanner(nID){this.fAboveTheFoldSupported=((typeof(ebO.btf)!="undefined")&&ebO.btf);if(this.fAboveTheFoldSupported){this.temp=ebCAboveTheFoldManager;this.temp(gEbStdGlobals.TIBase,true);delete this.temp;}if(this.fAboveTheFoldSupported){this.temp=ebCTimerManager;this.temp();delete this.temp;}this.nAdID=-1;this.strRand="";this.fClicked=false;this.strWmode="opaque";this.strRef="gEbStdBanners[" + nID + "]";this.nType=0;this.title="";this.strFlashObjID="";this.strImgID="";this.strJumpURL="";this.strJumpTarget="_blank";this.strWinAttr="";this.strClickAURL="";this.strClickNURL="";this.strClickVURL="";this.clickAImg=new Image(1,1);this.clickNImg=new Image(1,1);this.clickVImg=new Image(1,1);this.InterPipeImg=new Image(1,1);this.sAdVersions="";this.sTAId="";this.sClickedVersion="";this.sAdBasePath="";this.sDGId="";this.fProductClicked=new Object();this.handleInteraction=handleInteraction;this.ebversiontrackingimpression=ebversiontrackingimpression;this.redirect=redirect;this.interactions=new Array();this.getReportingPage=getReportingPage;this.getBannerRedirectUrl=getBannerRedirectUrl;this.strPendingInteractions="";this.doOnUnload=doOnUnload;this.doOnResize=doOnResize;this.doOnScroll=doOnScroll;this.getBannerResId=getBannerResId;init(this);function ebversiontrackingimpression(args){try{if(!ebIsPreview()){var urls=args.split("");for(var i=0;i<urls.length;i++){var url=urls[i];if(url){var img=new Image();img.src=url;}}}}catch(e){}}function handleInteraction(args){try{if(ebIsPreview()&&(typeof(window.parent.ebHandleFsCommandsPrev)=="function")){var params=(typeof(args)!="undefined") ? args : "";window.parent.ebHandleFsCommandsPrev("ebClickthrough", params, "Banner");}}catch(e){}this.sClickedVersion="";if(this.sAdVersions!=""){if(typeof(args)!="undefined"){if(args.indexOf("SV2:") == 0 && args.indexOf("")!=-1){var params=args.substring(4,args.length);params=params.split("");this.strJumpURL=gEbStdGlobals.checkUrl(params[0]);this.sClickedVersion=params[1];if(typeof(this.fProductClicked[this.sClickedVersion])=="undefined"){this.fProductClicked[this.sClickedVersion]=true;this.strClickVURL=(params.length==3)?params[2]:"";}else this.fProductClicked[this.sClickedVersion]=false;}}}if(this.strJumpURL=="")return;var fIsClick=!this.fClicked;if(this.strJumpTarget!="_blank"){if(fIsClick){reportRS(this.strClickNURL,this.clickNImg,this.strRand);reportRS(this.strClickAURL,this.clickAImg,this.strRand);this.fClicked=true;}if(this.sClickedVersion&&this.fProductClicked[this.sClickedVersion]){reportRS(this.strClickVURL,this.clickVImg,this.strRand);}window.setTimeout(ebFormat("{0}.redirect({1});",this.strRef,fIsClick),1000);}else {this.redirect(fIsClick);if(!ebIsPreview()){if(fIsClick){reportRS(this.strClickNURL,this.clickNImg,this.strRand);reportRS(this.strClickAURL,this.clickAImg,this.strRand);reportRS(this.strClickVURL,this.clickVImg,this.strRand);this.fClicked=true;}if(this.sClickedVersion&&this.fProductClicked[this.sClickedVersion]){reportRS(this.strClickVURL,this.clickVImg,this.strRand);}}}}function redirect(fIsClick){var url=(ebIsPreview()||gEbFlyLocal)?this.strJumpURL:this.getBannerRedirectUrl(fIsClick);if((this.strFlashObjID=="")||!useFlashRedirect(this.strFlashObjID,url,this.strJumpTarget))window.open(url,this.strJumpTarget,this.strWinAttr);}function getBannerRedirectUrl(fCountAsClick){if(typeof(fCountAsClick)=="undefined")fCountAsClick=true;var url=ebFormat("{0}{1}/BurstingPipe/adServer.bs?cn=brd&Page={2}&PluID={3}&Pos={4}&EyeblasterID={5}",ebStrProtocol,ebBS,this.getReportingPage(this.strPage),ebPluID,this.strRand,this.nAdID);if(this.nType==0)url+="&di=0";var fIsMassV=(this.sAdVersions!="");if(fIsMassV){if(this.sClickedVersion){url+=ebFormat("&vid={0}",this.sClickedVersion);url+="&vcl=1";var sJumpURL=this.strJumpURL.replace(/#/g,"%23");url+=ebFormat("&rtu=$${0}$$",sJumpURL);}else url+=ebFormat("&vid={0}",ebGetVersionToReport(this));}if(!fCountAsClick){var sClick="0";var fFirstClkOnV=(this.sClickedVersion&&this.fProductClicked[this.sClickedVersion]);if(fFirstClkOnV)sClick="2";url+=ebFormat("&clk={0}",sClick);}url+=ebGetTargetingParams(this);return url;}function init(objRef){copyServerData(objRef);setInteractions(objRef);if(objRef.fAboveTheFoldSupported)setEvents();addBanner(objRef);}function doOnUnload(){gEbStdGlobals.TIBase.clearAllEvents();}function doOnResize(){if(this.fAboveTheFoldSupported)this.checkIfAboveTheFold(this.getBannerResId());}function doOnScroll(){if(this.fAboveTheFoldSupported)this.checkIfAboveTheFold(this.getBannerResId());}function setEvents(){gEbStdGlobals.TIBase.addEventHandler("scroll","ebOnScrollStd");gEbStdGlobals.TIBase.addEventHandler("resize","ebOnResizeStd");gEbStdGlobals.TIBase.addEventHandler("unload","ebOnUnloadHandlerStd");if(!ebIsPreview()){gEbStdGlobals.TIBase.addEventHandler("beforeunload","ebReportAllInteractionsStd");gEbStdGlobals.TIBase.addEventHandler("unload","ebReportAllInteractionsStd");}}function copyServerData(objRef){objRef.nAdID=ebO.ai;objRef.strPage=ebO.p;objRef.strRand=ebO.rnd;objRef.sAdVersions=(ebO.av)?ebO.av:"";objRef.sTAId=(ebO.ta&&ebO.ta!="-1") ? ebO.ta : "";objRef.sAdBasePath=(ebO.abp)?ebO.abp:"";objRef.sDGId=(ebO.dg&&ebO.dg!="-1") ? ebO.dg : "";if(typeof(ebO.wm)!="undefined")objRef.strWmode=ebO.wm;if(typeof(ebO.title)!="undefined")objRef.title=ebO.title;copyServerClickData(objRef);}function setInteractions(objRef){if(objRef.fAboveTheFoldSupported){var inter=objRef.interactions["ebabovethefold"] = new ebCInteractionStd("ebAboveTheFold",0);inter.numLeftToReport=1;objRef.interactions["ebabovethefoldduration"] = new ebCInteractionStd("ebAboveTheFoldDuration",1);inter=objRef.interactions["ebbelowthefold"] = new ebCInteractionStd("ebBelowTheFold",0);inter.numLeftToReport=1;}}function copyServerClickData(objRef){if(!ebIsGlobalDef("ebO.ju"))return;objRef.strJumpURL=unescape(ebO.ju);if(ebIsPreview())objRef.strJumpTarget="_blank";else {switch(ebO.jt){case 0:objRef.strJumpTarget="_self";break;case 1:objRef.strJumpTarget="_blank";break;case 2:objRef.strJumpTarget="_top";break;}}objRef.strWinAttr="titlebar=1,resizable=1,scrollbars=1,directories=0,toolbar=1,status=1,";objRef.strWinAttr+="location="+ebO.jwloc+",menubar="+ebO.jwmb+",left="+ebO.jwl+",top="+ebO.jwt;if(ebO.jww>0)objRef.strWinAttr+=",width="+ebO.jww;if(ebO.jwh>0)objRef.strWinAttr+=",height="+ebO.jwh;if(ebIsGlobalDef("gEbBAd") && gEbBAd && ebIsGlobalDef("gEbBAd.AClickUrl"))objRef.strClickAURL=gEbBAd.AClickUrl;else if(ebIsGlobalDef("ebO.acu"))objRef.strClickAURL=unescape(ebO.acu);if(ebIsGlobalDef("ebO.ncu"))objRef.strClickNURL=unescape(ebO.ncu);}function addBanner(objRef){if(typeof(ebO.op)!="undefined")eval(unescape(ebO.op));collectURL(objRef);var fShowFlash=false;if((typeof(ebO.fv)!="undefined")&&(gEbStdGlobals.flFlashVer>=ebO.fv))fShowFlash=(gEbBC.isMac())?isMacFlashSupported(objRef):true;if(fShowFlash)addBannerFlash(objRef);else {addBannerImg(objRef);objRef.nType=1;}if(objRef.fAboveTheFoldSupported){if(ebO.fv>=6){var objProp=new Object();objProp.id="ebReportingFlash";objProp.name="ebReportingFlash";objProp.url=ebBigS+"/Res/Empty_Movie.swf";;objProp.fv=ebO.fv;objProp.w="0";objProp.h="0";objProp.play="false";objProp.strFlashParams="";objProp.strWmode="window";objProp.title="";objProp.position="absolute";var strBannerTags=buildFlashTags(objProp);document.write(strBannerTags);}}}function addBannerFlash(objRef){objRef.strFlashObjID="ebStdBanner"+gEbStdBanners.length;var strFlashUrl=unescape(ebO.fu);if(!gEbFlyLocal)strFlashUrl=ebResourcePath+"/"+strFlashUrl;var handler=objRef.strFlashObjID+'_DoFSCommand(command,args)';var strBannerTags='<scr'+'ipt>function ' + handler + '{try{command = command.replace(/FSCommand:/ig,"");if((command.toLowerCase()=="ebinteraction") || (command.toLowerCase()=="ebclickthrough"))';strBannerTags+=objRef.strRef+'.handleInteraction(args);';strBannerTags+='else if(command.toLowerCase()=="ebversiontrackingimpression")';strBannerTags+=objRef.strRef+'.ebversiontrackingimpression(args);';strBannerTags+='}catch(e){}}';strBannerTags+='function ebIsFlashExtInterfaceExist(){return true;}';strBannerTags+='</scr'+'ipt>';var objProp=new Object();objProp.id=objRef.strFlashObjID;objProp.name=objRef.strFlashObjID;objProp.url=strFlashUrl;objProp.fv=ebO.fv;objProp.w=ebO.w;objProp.h=ebO.h;objProp.strFlashParams=getFlashParams(objRef);objProp.strWmode=objRef.strWmode;objProp.title=objRef.title;strBannerTags+=buildFlashTags(objProp,handler);document.write(strBannerTags);}function buildFlashTags(objProp,handler){var strBannerTags="";if(typeof(objProp.play)=="undefined")objProp.play="true";if(typeof(objProp.strWmode)=="undefined")objProp.strWmode="opaque";if(gEbBC.isIE()){if(typeof(handler)!="undefined")strBannerTags+='<scr'+'ipt for="' + objProp.id + '" event="FSCommand(command,args)">try{'+handler+';}catch(e){}</scr'+'ipt>';strBannerTags+='<object id="'+ objProp.id +'" name ="'+objProp.name;strBannerTags+='" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase='+ebStrProtocol+'download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#';strBannerTags+='version=' + objProp.fv +',0,0,0 ';if(typeof(objProp.position)!="undefined")strBannerTags+='style="width:' + objProp.w + 'px;height:' + objProp.h + 'px;position:' + objProp.position + '"';else strBannerTags+='style="width:' + objProp.w + 'px;height:' + objProp.h + 'px"';strBannerTags+=' title="' + objProp.title + '"';strBannerTags+='><PARAM NAME="movie" VALUE="'+objProp.url;if(objProp.fv>=6&&objProp.strFlashParams!="")strBannerTags+='">'+'<PARAM NAME="FlashVars" VALUE="'+objProp.strFlashParams+'">';else {if(objProp.strFlashParams!="")strBannerTags+='?' + objProp.strFlashParams + '">';else strBannerTags+='">';}strBannerTags+='<PARAM NAME="play" VALUE=' + objProp.play + '>';strBannerTags+='<PARAM NAME="wmode" VALUE="' + objProp.strWmode +'"><PARAM NAME="menu" VALUE=false><PARAM NAME="allowScriptAccess" value="always"></object>';}else {strBannerTags+='<EMBED src="'+objProp.url;if(objProp.fv>=6&&objProp.strFlashParams!="")strBannerTags+='" FlashVars="' + objProp.strFlashParams + '" ';else {if(objProp.strFlashParams!="")strBannerTags+='?'+ objProp.strFlashParams +'"';else strBannerTags+='"';}if(typeof(objProp.position)!="undefined")strBannerTags+='style="width:' + objProp.w + 'px;height:' + objProp.h + 'px;position:' + objProp.position + '"';else strBannerTags+='style="width:' + objProp.w + 'px;height:' + objProp.h + 'px"';strBannerTags+=' play=' + objProp.play + ' '+'id="' + objProp.id + '"name="' + objProp.name + '" quality=high ';strBannerTags+='wmode="' + objProp.strWmode + '" menu=false TYPE="application/x-shockwave-flash" PLUGINSPAGE="' + ebStrProtocol + 'www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" ';strBannerTags+='allowScriptAccess="always"' + ' title="' + objProp.title + '"' + '></EMBED>';}return strBannerTags;}function addBannerImg(objRef){objRef.strImgID="ebStdBanner"+gEbStdBanners.length;var strImgUrl=unescape(ebO.iu);if(!gEbFlyLocal)strImgUrl=ebResourcePath+"/"+strImgUrl;strBannerTags="";var fNoFlashRes=(typeof(ebO.fv)=="undefined");var strImgSrc;if((ebIsPreview())||fNoFlashRes)strImgSrc=strImgUrl;else {strImgSrc=ebStrProtocol+ebBS+'/BurstingPipe/adServer.bs?cn=cdi&ai=' + ebO.ai + '&p=' + objRef.strPage + '&pi=' + ebPluID + '&ru=' + strImgUrl + '&ord='+objRef.strRand;;strImgSrc+=ebGetTargetingParams(objRef);}var strCursor=(objRef.strJumpURL!="") ? "cursor:pointer;cursor:hand;" : "cursor:auto;";strBannerTags+='<img src="' + strImgSrc + '" id="' + objRef.strImgID+ '" width=' + ebO.w +' height=' + ebO.h + ' title="' + objRef.title + '"' + ' onclick="' + objRef.strRef + '.handleInteraction()" style="'+strCursor+'"></img>';document.write(strBannerTags);}function getFlashParams(objRef){var strDomain=gEbStdGlobals.getHostName();var conduitPath=ebBigS+"/res/ebV" + ebConduitVer + "_";var interactionTime=ebBigS+"/Res/ebInteractionTime" + ebIntTimeVer + ".swf";var clickTagHandler=getClickTagURL(objRef);var strFSCmdHandler="";if(!gEbBC.isIE())strFSCmdHandler=objRef.strFlashObjID+"_DoFSCommand";var strUrl="ebDomain="+strDomain+"&ebAdID="+objRef.nAdID+"&cp="+conduitPath+"&clickTag="+escape(clickTagHandler)+"&clickTAG="+escape(clickTagHandler)+"&ebIntTime="+interactionTime+"&ebFSCmdHandler="+strFSCmdHandler+"&clickTARGET="+objRef.strJumpTarget;strUrl+=setSmartVersioningFlashVars(objRef);return strUrl;}function setSmartVersioningFlashVars(objRef){var xmlPath="";var smartFlashVars="";var tempAd;eval('try{tempAd=new ebAd_' +objRef.nAdID+ '()}catch(e){tempAd=null;ebDebug("setXMLPathFlashVars: No AdJS was Loaded","blue");}');if(tempAd!=null){adjustAdObject(tempAd);var fIsMassV=(objRef.sAdVersions!="");if((typeof(tempAd.strXML)!="undefined") && (tempAd.strXML != "")&&!fIsMassV){xmlPath=tempAd.strXML;if((typeof(ebAdXmlPath)!="undefined") && (ebAdXmlPath != ""))xmlPath=ebAdXmlPath;else if(!gEbFlyLocal)xmlPath=ebResourcePath+xmlPath;smartFlashVars=ebFormat("&ebAdXML={0}&{1}",xmlPath,buildAdditionalResStr(tempAd));}else if(fIsMassV){if((typeof(tempAd.strDisplayMap)=="undefined")||!tempAd.strDisplayMap){return "";}var sDisplayMap=tempAd.strDisplayMap;var sResPath=(gEbFlyLocal)?"":ebResourcePath;if((typeof(sDisplayMap)!="undefined") && (sDisplayMap != ""))smartFlashVars+=ebFormat("&ebAdVersions={0}&ebAdMap={1}&ebResPath={2}&ebAdSVBasePath={3}&{4}",objRef.sAdVersions,sDisplayMap,sResPath,objRef.sAdBasePath,buildAdditionalResStr(tempAd));}}return smartFlashVars;}function buildAdditionalResStr(objRef){var strAdditionalRes="";var assets=objRef.additionalAssetsArray;for(var strName in assets){try{if(!(assets[strName] instanceof Array))continue;var asset=assets[strName];strAdditionalRes=getNameAsset(strName,strAdditionalRes);var info=getAssetProperties(objRef,strName);strAdditionalRes+=getUrlAsset(info.strURL);}catch(e){}}for(var name in objRef.nonVideoAssets){try{if(typeof(objRef.nonVideoAssets[name].url)=="undefined"){continue;}strAdditionalRes=getNameAsset(name,strAdditionalRes);strAdditionalRes+=getUrlAsset(objRef.nonVideoAssets[name].url);}catch(e){}}return strAdditionalRes;}function getAssetProperties(objRef,strMovieName){try{var asset=objRef.additionalAssetsArray[strMovieName];for(var i=0;i<asset.length;i++){if(asset[i]){return asset[i][0];}}}catch(e){}}function getNameAsset(name,additionalRes){if(additionalRes!="")additionalRes+="&";additionalRes+=name+"=";return additionalRes;}function getUrlAsset(urlAdditionalAsset){var additionalRes="";additionalRes+=(gEbFlyLocal)?urlAdditionalAsset:ebResourcePath+urlAdditionalAsset;return additionalRes;}function reportRS(strURL,reportImg,strRand){if(strURL=="")return;strURL=strURL.replace(/\[ebRandom\]/ig,strRand);strURL=strURL.replace(/\[timestamp\]/ig,strRand);reportImg.src=strURL;}function getClickTagURL(objRef){var strURL;if(ebIsPreview()){strURL=gEbFlyLocal?"ReportPage_" + HTMLPageVer + ".html":objRef.strJumpURL;}else {var strReportUrl=objRef.getBannerRedirectUrl();var strAReportUrl=objRef.strClickAURL;var strNReportUrl=objRef.strClickNURL;strURL=ebBigS+"/ReportPage" + ebReportPageVer + ".html"+"?ebReportURL="+escape(strReportUrl)+"$$ebNReportURL="+escape(strNReportUrl)+"$$ebAReportURL="+escape(strAReportUrl)+"$$ebImpressionID="+objRef.strRand;}return strURL;}function isMacFlashSupported(objRef){var fSupported=true;var nMinAdIDNoNeedVer8=0;if(ebBS.indexOf("dev")!=-1)nMinAdIDNoNeedVer8=48440;else if(ebBS.indexOf("int")!=-1)nMinAdIDNoNeedVer8=180990;else if(ebBS.indexOf("pilot")!=-1)nMinAdIDNoNeedVer8=227853;else nMinAdIDNoNeedVer8=260500;if((objRef.nAdID<nMinAdIDNoNeedVer8)&&(gEbStdGlobals.flFlashVer<8)){fSupported=false;}return fSupported;}function collectURL(objRef){try{if(ebIsPreview())return;var fCollectURL=(typeof(ebO.cu)!="undefined");if(fCollectURL){var adId=objRef.nAdID;var url=gEbStdGlobals.getMainPageURL();var img=new Image();img.src=ebStrProtocol+ebBS+'/BurstingPipe/adServer.bs?cn=curl&ai='+adId+'&url=$$'+url+'$$';}}catch(e){}}function useFlashRedirect(flashObjID,strJumpURL,strJumpTarget){var flashObj=document.getElementById(flashObjID);if(!flashObj)return false;var redirectFunc="ebOpenJumpURL";var fIsAS3=(typeof(flashObj[redirectFunc])!="undefined");var fUseFlash=false;if((gEbBC.isSafari())&&fIsAS3){try{fUseFlash=flashObj[redirectFunc](strJumpURL,strJumpTarget);}catch(e){fUseFlash=false;}}return fUseFlash;}function getReportingPage(strPage){var strFinalPage=strPage;strFinalPage=strFinalPage.replace(/\~/ig,"_");strFinalPage=strFinalPage.replace(/\^/ig,"_");strFinalPage=strFinalPage.replace(/\|/ig,"_");return escape(strFinalPage);}function getBannerResId(){return this.nType?this.strImgID:this.strFlashObjID;}function adjustAdObject(tempAd){if(typeof(tempAd.additionalAssetsArray)=="undefined"){tempAd.additionalAssetsArray=new Object();for(i in tempAd.additionalAssets){var newAsset=tempAd.additionalAssetsArray[i]=new Array;for(asset in tempAd.additionalAssets[i]){var info=tempAd.additionalAssets[i][asset].length>0?tempAd.additionalAssets[i][asset]:null;if(info!=null)newAsset[asset]=info;}}}}}function ebCStdGlobals(){this.flFlashVer=0;this.nDbgLvl=0;this.fPreview=false;this.debugWin=null;this.init=init;this.getHostName=getHostName;this.getMainPageURL=getMainPageURL;this.checkUrl=checkUrl;function init(){this.fPreview=((typeof(ebO.pr)!="undefined")&&ebO.pr);this.nDbgLvl=ebO.d;flashDetection(this);}function flashDetection(objRef){var flFlashVer;try{var flashDetector=new ebCFlashDetector();flFlashVer=(gEbBC.isIE())?flashDetector.getIEFlash():flashDetector.getMozillaFlash();gEbStdGlobals.flFlashVer=flFlashVer;}catch(e){gEbStdGlobals.flFlashVer=0;}}function getHostName(){var strPage="";if(document.location.toString().indexOf("javascript:")==0)eval('try{strPage = parent.document.location.hostname;}catch(e){strPage = "";}');else eval('try{strPage = document.location.hostname;}catch(e){strPage = "";}');return strPage;}function getMainPageURL(){var url="";try{url=top.document.URL;}catch(e){}return url;}function checkUrl(strURL){var lowerUrl=strURL.toLowerCase();if((lowerUrl.indexOf("http://")==-1)&&(lowerUrl.indexOf("https://")==-1)&&(lowerUrl.indexOf("ftp://")==-1)&&(lowerUrl.indexOf("aim:")==-1)&&(lowerUrl.indexOf("mailto:")==-1)){strURL="http://"+strURL;}return strURL;}}function ebIsPreview(){return (gEbStdGlobals.fPreview);}function ebLoadScript(strScriptID,strScriptSrc){if(strScriptSrc)document.write("<scr"+"ipt id="+ strScriptID + " src=" + strScriptSrc +"></scr"+"ipt>");}function ebLoadIframe(strIframeSrc){if(strIframeSrc)document.write("<iframe src="+ strIframeSrc +" width=0 height=0 frameborder=0></iframe>");}function ebDebug(msg,color){}if(typeof(ebO.osd)!="undefined")eval(unescape(ebO.osd));if(typeof(gEbStdGlobals)=="undefined"){gEbStdGlobals=new ebCStdGlobals();gEbStdGlobals.init();}if((typeof(ebCTagInsertorBase)!="undefined") && (typeof(gEbStdGlobals.TIBase) == "undefined"))gEbStdGlobals.TIBase=new ebCTagInsertorBase();if(typeof(gEbStdBanners)=="undefined")gEbStdBanners=new Array();gEbCurStdBanner=gEbStdBanners[gEbStdBanners.length]=new ebCStdBanner(gEbStdBanners.length);if(gEbCurStdBanner.fAboveTheFoldSupported){var strFunc=ebFormat("{0}.checkIfAboveTheFold('{1}')",gEbCurStdBanner.strRef,gEbCurStdBanner.getBannerResId());window.setTimeout(strFunc,100);}gEbnMaxTimerTime=15*1000*60;if(typeof(gEbfIntReported)=="undefined")gEbfIntReported=false;if(typeof(ebMaxTimePassed)=="undefined")ebMaxTimePassed=false;if(!ebIsPreview()&&(gEbStdBanners[gEbStdBanners.length-1].fAboveTheFoldSupported)){window.setTimeout("ebMaxTimeStd()",gEbnMaxTimerTime);if(gEbBC.isOpera()){if(typeof(gEbnIntSeq)=="undefined"){gEbnMaxTimerTime+=5000;gEbnIntSeq=0;window.setTimeout("ebReportTimersInterval()",gEbnIntSeqArray[gEbnIntSeq]*1000);}}}ebO=null;function ebCFlashDetector(){this.getIEFlash=getIEFlash;this.getMozillaFlash=getMozillaFlash;function getIEFlash(){var strFlashVersion=getMajorMinorFlashVersion(7);var activeX;if(!strFlashVersion){try{activeX=new ActiveXObject("ShockwaveFlash.ShockwaveFlash.6");strFlashVersion="WIN 6,0,21,0";activeX.AllowScriptAccess="always";strFlashVersion=activeX.GetVariable("$version");}catch(e){if(!activeX)strFlashVersion=getMajorMinorFlashVersion(3);}}strFlashVersion=splitFlashMajorMinorVersions(strFlashVersion);var nFlashVer=Number(strFlashVersion);return isNaN(nFlashVer)?0:nFlashVer;}function getMajorMinorFlashVersion(nVersion){try{var activeX=new ActiveXObject("ShockwaveFlash.ShockwaveFlash."+nVersion);return activeX.GetVariable("$version");}catch(e){return "";}}function splitFlashMajorMinorVersions(strFlashVersion){if(strFlashVersion){var tempArray=strFlashVersion.split(" ");var tempString=tempArray[1];var versionArray=tempString.split(",");var versionMajor=versionArray[0];var versionMinor=versionArray[1];var versionRevision=versionArray[2];return versionMajor+"."+versionMinor+versionRevision;}return 0;}function getMozillaFlash(){var ver=0;var releaseVer=0;var versionMajor=0;var versionMinor=0;var versionRevision=0;if(navigator.plugins!=null&&navigator.plugins.length>0){if(navigator.plugins["Shockwave Flash"]){var flashDescription=navigator.plugins["Shockwave Flash"].description;var descArray=flashDescription.split(" ");var tempArrayMajor=descArray[2].split(".");versionMajor=tempArrayMajor[0];versionMinor=tempArrayMajor[1];versionRevision=descArray[3];if(versionRevision=="")versionRevision=descArray[4];if(isNaN(versionRevision[0]))versionRevision=versionRevision.substring(1);if(versionRevision.indexOf("d")>0)versionRevision=versionRevision.substring(0,versionRevision.indexOf("d"));}}var nFlashVer=Number(versionMajor+"."+versionMinor+versionRevision);if(isNaN(nFlashVer))return 0;if(((versionMajor==6)&&(versionRevision>=40))||(versionMajor>6))return nFlashVer;else return 0;}}