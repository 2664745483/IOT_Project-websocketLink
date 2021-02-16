<!-- 首页第一页 -->
<template>
	<div id="main" 
		:style="{overflow:isScrollerAuto?'auto':'hidden'}"
		v-on:touchstart = "mouseDown"
		v-on:touchmove  = "mouseMove"
		v-on:touchend  = "mouseOut"
	>
		<!-- 首页头部 -->
		<ul class="title">
			<li class="main-date">
				<p>
					<span>{{(dates.hours <=9?"0":"")+dates.hours}}</span><br/>
					<span>{{(dates.minute <=9?"0":"")+dates.minute}}</span>
				</p>
				<p>
					<span>{{dates.month}}月{{dates.day}}日 星期{{dates.date}} <input type="button" value="up" /></span><br />
					<span>阴33°C</span>
				</p>
			</li>
			<ul class="main-controll">
				<li class="main-log">
					<p>警告日志条数</p>
					<div id="echarts_post1">
						<template v-for="(item,indexs) in wenShiDuArray">
							<template v-for="(itemData,index) in item.data">
								<span 
									:style="{background:item.color,bottom:itemData+'%',left:index*2+'%'}"
								>
								</span>
							</template>
						</template>
					</div>
				</li>
				<ul class="main-btns">
					<li id="btn-info"></li>
					<li id="btn-message"></li>
					<li id="btn-edit"></li>
					<li id="btn-code"></li>
				</ul>
			</ul>
			
		</ul>
		<!-- 首页身体 -->
		<ul class="bodys">
			<li name="snedDeng">
				<div class="body-title">
					<p class="body-name">开关-灯</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span id="body-content-type-1">
						<!-- 输入信息数据 -->
						<span class="input">
							<div class="button"
								v-on:touchstart="body_content_type_1_down"
								v-on:touchmove="body_content_type_1_sendData"
							>
								<div class="slide" 
									:style="{height:body_content_type.snedDeng.height+'px'}"
								></div>
							</div>
						</span>
						<!-- 显示信息数据 -->
						<span class="output">
							<div class="img" :style="{opacity:body_content_type.snedDeng.returnRange/100}">
							</div>
						</span>
					</span>
				</div>
			</li>
			<li name="button">
				<div class="body-title">
					<p class="body-name">开关-按钮</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span class="body-content-type-button">
						<!-- 输入信息数据 -->
						<span class="input">
							<div class="button"  v-on:click="body_content_type_button">
								<div class="show"
									:style="{left:body_content_type.button.sendBool?'calc(0% + 3px)':'calc(100% - 37px )'}"
								>
									{{body_content_type.button.sendBool?"开启":"关闭"}}
									
								</div>
							</div>
						</span>
						<!-- 显示信息数据 -->
						<span class="output">
									{{body_content_type.button.returnBool?"已开启":"已关闭"}}
						</span>
					</span>
				</div>
			</li>
			<li name="wenShiDu1">
				<div class="body-title">
					<p class="body-name">温湿度-type1</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span class="body-content-type-wenShiDu">
						<!-- 输入信息数据 -->
						<span class="input">
							<div class="button"></div>
						</span>
						<!-- 显示信息数据 -->
						<span class="output">
									温度:{{body_content_type.wenShiDu1.wenDu}}°C<br/>
									湿度:{{body_content_type.wenShiDu1.shiDu}}%
						</span>
					</span>
				</div>
			</li>
			<li name="wenShiDu2">
				<div class="body-title">
					<p class="body-name">温湿度-type2</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span class="body-content-type-wenShiDu">
						<!-- 输入信息数据 -->
						<span class="input">
							<div class="button" ></div>
						</span>
						<!-- 显示信息数据 -->
						<span class="output">
									温度:{{body_content_type.wenShiDu2.wenDu}}°C<br/>
									湿度:{{body_content_type.wenShiDu2.shiDu}}%
						</span>
					</span>
				</div>
			</li>
			<li name="getBool">
				<div class="body-title">
					<p class="body-name">获取触发-type1</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span class="body-content-type-getBool">
						<!-- 输入信息数据 -->
						<span class="input">
							<div class="button" ></div>
						</span>
						<!-- 显示信息数据 -->
						<span class="output" :style="{color:body_content_type.getBool?'#0F0':'#F00'}">
									{{body_content_type.getBool?"已":"未"}}触发
						</span>
					</span>
				</div>
			</li>
			<li name="button1">
				<div class="body-title">
					<p class="body-name">开关-继电器</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span class="body-content-type-button">
						<!-- 输入信息数据 -->
						<span class="input">
							<div class="button"  v-on:click="body_content_type_button1">
								<div class="show"
									:style="{left:body_content_type.button1.sendBool?'calc(0% + 3px)':'calc(100% - 37px )'}"
								>
									{{body_content_type.button1.sendBool?"开启":"关闭"}}
									
								</div>
							</div>
						</span>
						<!-- 显示信息数据 -->
						<span class="output">
									{{body_content_type.button1.returnBool?"已开启":"已关闭"}}
						</span>
					</span>
				</div>
			</li>
			<li name="leiDa">
				<div class="body-title">
					<p class="body-name">雷达-类型1</p>
					<p class="body-info">这个人很懒没有留下什么</p>
					<!-- 状态 -->
					<span class="body-start"></span>
				</div>
				<!-- 控制器的多态类别 -->
				<div class="body-content">
					<span class="body-content-type-leiDa">
						<!-- 输入信息数据 -->
						<span class="input">
							
						</span>
						<!-- 显示信息数据 -->
						<span class="output">
									<!-- {{body_content_type.leiDa.jiaoDu}}<br/>
									{{body_content_type.leiDa.changDu}} -->
								<span v-for="(item ,index) in body_content_type.leiDa" 
								:style="{transform:'rotate('+(-item.jiaoDu+55)+'deg)'}">
									
									<span :style="{height:'calc('+((item.changDu/2000)*100)+'%)',bottom:'20%',background:item.reg}" ></span>
								</span>
						</span>
					</span>
				</div>
			</li>
		</ul>
	</div>
</template>

<script>
	export default{
		components:{
			
		},
		data(){
			return{
				isScrollerAuto:true,    //是否自动滚动   
				mouseData:{			//鼠标的事件
					isDown:false,		//是否按下
					downPosition:{		//按下时位置
						x:0,
						y:0,
					},
					thisPosition:{		//当前位置
						x:0,
						y:0,
					},
				},
				dates:{					//日期
					years:"0000",
					month:"00",
					date:"00",
					day:"00",
					hours:"00",
					minute:"00"
				},
				wenShiDuArray:[
					{
						color:'#F00',
						data:[]
					},
					{
						color:'#ff8419',
						data:[]
					},
				],
				body_content_type:{   //当前控件的信息
					snedDeng:{			//控制灯的亮度
						sendDateOnRepeat:0,  //发送值不可重复
						returnRange:100,	//返回亮度 1~100
						sendRange:0,	//发送亮度 1~100
						height:40,    //范围是 40~150  
						BofferHeight:0,
						minHeight:40,
						maxHeight:150,
						isDown:false,		//是否按下
						downPosition:{		//按下时位置
							x:0,
							y:0,
						},
						thisPosition:{		//当前位置
							x:0,
							y:0,
						}
					},
					button:{				//开关控制
						returnBool:false,
						sendBool:false,
					},
					button1:{				//开关控制
						returnBool:false,
						sendBool:false,
					},
					wenShiDu1:{
						wenDu:0,
						shiDu:0
					},
					wenShiDu2:{
						wenDu:0,
						shiDu:0
					},
					getBool:false,
					leiDa:[
						
					]
				},
				
			}
		},
		methods:{
			// 鼠标按下
			mouseDown:function(e){
				// console.log("down",e.touches[0]);
				this.mouseData.isDown = true;  
				let touchData = e.touches[0];
				this.mouseData.downPosition.x = touchData.clientX;
				this.mouseData.downPosition.y = touchData.clientY;
			},
			//鼠标滑动
			mouseMove:function(e){
				// console.log("move",e);
				let touchData = e.touches[0];
				this.mouseData.thisPosition.x = touchData.clientX;
				this.mouseData.thisPosition.y = touchData.clientY;
			},
			//鼠标弹起 - 解除滚动锁定
			mouseOut:function(e){
				// console.log("out",e);
				this.mouseData.isDown = false;
				this.setScrollerAuto(!this.mouseData.isDown);
			},
			//是否滚动的方法
			setScrollerAuto:function(boolData){
				this.isScrollerAuto = boolData;
			},
			//刷新时间
			setDate:function(){
				let date = new Date();
				
				this.dates.years = date.getYear();
				this.dates.month = date.getMonth()+1;
				switch(date.getDay()){
					case 1:{
						this.dates.date = "一";
						break;
					}
					case 2:{
						this.dates.date = "二";
						break;
					}
					case 3:{
						this.dates.date = "三";
						break;
					}
					case 4:{
						this.dates.date = "四";
						break;
					}
					case 5:{
						this.dates.date = "五";
						break;
					}
					case 6:{
						this.dates.date = "六";
						break;
					}
					case 7:{
						this.dates.date = "七";
						break;
					}
				}
				
				this.dates.day = date.getDate();
				// this.dates.hours = date.getHours();
				if( date.getHours() >= 13){
					if(date.getHours()-12 <= 9){
						this.dates.hours =  date.getHours()-12;
					}
				}
				this.dates.minute = date.getMinutes();
				
			},
			addWenShiDuArray:function(){
				
				for(var i = 0;i<2;i++){
					if(this.wenShiDuArray[i].data.length >= 40){
						this.wenShiDuArray[i].data.splice(0, 1)
					}
					
					
					this.wenShiDuArray[i].data.push(this.body_content_type[i==0?'wenShiDu1':'wenShiDu2'].wenDu+"");
				}
				
				
				
			},
			//当前是控件里面的内容
			body_content_type_1_down:function(e){
				// console.log("按钮down");
				this.setScrollerAuto(false);  //锁定控制器
				let touchData = e.touches[0];
				this.body_content_type.snedDeng.downPosition.y = touchData.clientY;
				this.body_content_type.snedDeng.BofferHeight = this.body_content_type.snedDeng.height;  //定义当前缓存高度数据
			},
			body_content_type_1_move:function(e){
				let returnFunction;
				// console.log("按钮move");
				let touchData = e.touches[0];
				this.body_content_type.snedDeng.thisPosition.y = touchData.clientY;
				
				// 判断当前是否大还是小
				// console.log("按钮move",this.body_content_type.snedDeng.thisPosition.y);
				let thisHeight = this.body_content_type.snedDeng.BofferHeight;
				if(this.body_content_type.snedDeng.downPosition.y < this.body_content_type.snedDeng.thisPosition.y){
					//计算相差向上的相差
					let thisHeightMeath = this.body_content_type.snedDeng.thisPosition.y - this.body_content_type.snedDeng.downPosition.y;
					thisHeight = this.body_content_type.snedDeng.BofferHeight-thisHeightMeath;
				}else{
					//计算相差向下的相差
					let thisHeightMeath =  this.body_content_type.snedDeng.downPosition.y - this.body_content_type.snedDeng.thisPosition.y;
					thisHeight = this.body_content_type.snedDeng.BofferHeight+thisHeightMeath;
				}
				// console.log(thisHeight);
				//判断数据是否合格
				
				
				var then1 = {
					"then":(functions)=>{
						if(
							(this.body_content_type.snedDeng.maxHeight > thisHeight)
							&&
							(thisHeight > this.body_content_type.snedDeng.minHeight)
						){
							
							
							this.body_content_type.snedDeng.height = thisHeight;
						}else if(this.body_content_type.snedDeng.maxHeight < thisHeight){
							
							this.body_content_type.snedDeng.height = this.body_content_type.snedDeng.maxHeight;
							
						}else if(this.body_content_type.snedDeng.minHeight > thisHeight){
							
							this.body_content_type.snedDeng.height = this.body_content_type.snedDeng.minHeight;
							
						}
						
						let sendData = Math.round(
								(
									(
										this.body_content_type.snedDeng.height-
										this.body_content_type.snedDeng.minHeight 
									)/
									(
										this.body_content_type.snedDeng.maxHeight-
										this.body_content_type.snedDeng.minHeight  
									)  
								)*100
							);
						if(this.body_content_type.snedDeng.sendDateOnRepeat != sendData){
							// console.log(this.body_content_type.snedDeng.sendDateOnRepeat , sendData);
							functions(
								sendData
							 );
						}
						this.body_content_type.snedDeng.sendDateOnRepeat = sendData;
						
						
					}
				}
				return then1;
			},
			body_content_type_1_sendData:function(e){
				// console.log(e);
				let event = e;
				this.body_content_type_1_move(event).then((data)=>{
					
					// console.log(data);
					// this.body_content_type.snedDeng.returnRange = data;
					
					this.sendSocket('2','range',data);
				})
				
			},
			body_content_type_1_returnData:function(e){
				// console.log("返回值:",e);
					this.body_content_type.snedDeng.returnRange = e;
			},
			
			
			
			body_content_type_button:function(){
				this.body_content_type.button.sendBool = !this.body_content_type.button.sendBool;
				this.sendSocket('2','bool',this.body_content_type.button.sendBool );
			},
			body_content_type_button_returnData:function(e){
				// console.log("返回值:",e);
				this.body_content_type.button.returnBool = e;
			},
			body_content_type_wenShiDu1_returnData:function(e){
				// console.log("返回值:",e);
				this.body_content_type.wenShiDu1.wenDu = e[0];
				this.body_content_type.wenShiDu1.shiDu = e[1];
			},
			body_content_type_wenShiDu2_returnData:function(e){
				// console.log("返回值:",e);
				this.body_content_type.wenShiDu2.wenDu = e[0];
				this.body_content_type.wenShiDu2.shiDu = e[1];
				// this.body_content_type.button.returnBool = e;
			},
			
			body_content_type_getBool_returnData:function(e){
				console.log("返回值:",e);
				this.body_content_type.getBool = e;
			},
			
			
			body_content_type_button1:function(){
				this.body_content_type.button1.sendBool = !this.body_content_type.button1.sendBool;
				this.sendSocket('2','bool1',this.body_content_type.button1.sendBool );
			},
			body_content_type_button1_returnData:function(e){
				// console.log("返回值:",e);
				this.body_content_type.button1.returnBool = e;
			},
			
			
			body_content_type_leiDa_returnData:function(e){
				// console.log("返回值:",e);
				// this.body_content_type.leiDa.jiaoDu = e[0];
				// this.body_content_type.leiDa.changDu = e[1];
				let listId = -1;
				for (var i = 0; i < this.body_content_type.leiDa.length; i++) {
					if(this.body_content_type.leiDa[i].jiaoDu == e[0]){
						listId = i;
					}
					this.body_content_type.leiDa[i].reg = '#FFF';
				}
				if(listId == -1){
					this.body_content_type.leiDa.push({
						jiaoDu:e[0],
						changDu:e[1],
						reg:'#F00'
					});
				}else{
					this.body_content_type.leiDa[listId].jiaoDu = e[0];
					this.body_content_type.leiDa[listId].changDu = e[1]>=2000?2000:e[1];
					this.body_content_type.leiDa[listId].reg = '#F00';
				}
				
				// console.log(this.body_content_type.leiDa);
			},
			
		},
		created() {
			// setInterval(()=>{
			// 	this.isScrollerAuto = !this.isScrollerAuto;
			// 	console.log("锁定滚动");
			// },3000);
			
			
			setInterval(()=>{
				this.setDate();
				// send();
			},1000);
			
			this.setDate();
			
			
			
			//注册返回灯光亮度
			this.addReadMessageLine("range",this.body_content_type_1_returnData);
			this.addReadMessageLine("bool",this.body_content_type_button_returnData);
			this.addReadMessageLine("wenShiDu1",this.body_content_type_wenShiDu1_returnData);
			this.addReadMessageLine("wenShiDu2",this.body_content_type_wenShiDu2_returnData);
			this.addReadMessageLine("getBool",this.body_content_type_getBool_returnData);
			this.addReadMessageLine("bool1",this.body_content_type_button1_returnData);
			this.addReadMessageLine("leiDa",this.body_content_type_leiDa_returnData);
			
			
			
			setInterval(()=>{
				//定时获取值
				this.addWenShiDuArray();
				
			},400);
			
			
			
		}
	}
</script>

<style>
	#main{
		width: 100%;
		height: 100%;
		min-width: 375px;
		position: absolute;
		top:0px;
		left: 0px;
		/* background-image: url(../assets/template/app首页.png); */
		background-image: url(../assets/bg/bg.png);
		background-size: 100%;
		overflow: auto;
	}
	#main .title{
		margin-top: 30px;
		width: 100%;
		min-height:200px;
		background: #2C3E5055;
		display: flow-root;
	}
	#main .title li, #main .title ul {
	    height: 210px;
	    /* border: 1px solid red; */
	    float: left;
	    margin: 5px;
	    background: rgba(0, 0, 0, 0.8);
	    border-radius: 20px;
	}
	#main .title .main-date {
	    width: 140px;
	    color: #FFF;
	}
	#main .title .main-date p:nth-child(1){
		margin-top: 15px;
		font-size: 50px;
	}
	#main .title .main-date p:nth-child(2){
		margin-top: 11px;
		font-size: 12px;
		text-align: left;
		margin-left: 10px;
	}
	#main .title .main-date p:nth-child(2) input{
		background: none;
		border: none;
		background-image: url(/static/img/icons.4ba51dd.png);
		background-size: auto 170%;
		background-position: -107px -5px;
	}
	#main .title .main-controll{
		height: 210px;
		width: calc(100% - 12px*2 - 137px);
		background: none;
	}
	#main .title .main-controll *{
		margin: 0px;
	}
	#main .title .main-log{
		width: 100%;
		height: 140px;
		overflow: hidden;
	}
	#main .title .main-log p{
		font-size: 12px;
		color: #fff;
		font-weight: 600;
		line-height: 30px;
	}
	#main .title .main-log > div{
		width: 100%;
		height: calc(100% - 30px);
		background: #292a20;
		position: relative;
	}
	#main .title .main-log > div span{
		width: 5px;
		height: 5px;
		position: absolute;
		left: 0px;
		display: block;
		border-radius: 20px;
	}
	#main .title .main-btns{
		width: 100%;
		height: 60px;
		margin-top: 10px;
		text-align: center;
	}
	#main .title .main-btns > *{
		width: 45px;
		height: 45px;
		background: #FFFFFF33;
		margin: 8px 2px 0px;
		color: #FFF;
		background-image: url(../assets/icon/icons.png);
		background-size: auto 100%;
	}
	#main .title .main-btns #btn-info{
		margin-left: 10px;
		background-position: 0px 0px;
	}
	#main .title .main-btns #btn-message{
		background-position: -45px 0px;
	}
	#main .title .main-btns #btn-edit{
		background-position: -90px 0px;
	}
	#main .title .main-btns #btn-code{
		background-position: -135px 0px;
	}
	#main .bodys{
		padding-bottom: 40px;
		overflow: hidden;
		margin-bottom: 300px;
	}
	/* 当前内容列表 */
	#main .bodys > li{
		width: calc(50% - 20px);
		height: 160px;
		background: #2226;
		float: left;
		margin: 10px;
		border-radius: 20px;
		position: relative;
		backdrop-filter: blur(15px);
	}
	/* 当前列表头部信息 */
	#main .bodys  .body-title{
		width: calc(100% - 43px);
		height: 55px;
		background: #000C;
		border-radius: 15px;
		text-align: left;
		font-size: 15px;
		/* box-sizing: border-box; */
		/* padding: 5px 10px; */
		position: relative;
	}
	#main .bodys  .body-title .body-name{
		font-size: 15px;
		margin: 5px 0px 0px 10px;
	}
	#main .bodys  .body-title .body-info{
		font-size: 0.3rem;
		transform: scale(0.8);
		transform-origin: left top;
		width: 140px;
		color: #BBB;
		margin: 0px 0px 0px 10px;
	}
	#main .bodys  .body-title .body-start{
		position: absolute;
		bottom: 0px;
		/* left: 50%; */
		margin:2px 20px;
		width: calc(100% - 40px);
		height: 2px;
		border-radius: 10px;
		background: #0f0;
		box-shadow: 0px 0px 10px 0px #00FF00;
	}
	
	
	/* 写主要控制器的样式 */
	#body-content-type-1 .button{
		width: 35px;
		height: 100%;
		background: #000C;
		position: absolute;
		top: 0px;
		right: 0px;
		border-radius: 25px;
	}
	#body-content-type-1 .slide{
		width: calc(100% - 10px);
		height: 70%;
		position: absolute;
		bottom: 5px;
		left: 5px;
		background: url(../assets/icon/list.png),#FFF;
		background-size: 60% auto;
		background-repeat: no-repeat;
		background-position: center 13px;
		border-radius: 25px;
	}
	#body-content-type-1 .img{
		width: 70px;
		height: 70px;
		position: absolute;
		background:url(../assets/icon/lamplight.png);
		background-size: 100% auto;
		/* border:1px solid red; */
		opacity: 0.5;
		bottom: 20px;
		left: 50%;
		margin-left: -50px;
	}
	.body-content-type-button .output{
		width: 90px;
		height: 40px;
		position: absolute;
		background-size: 100% auto;
		bottom: 40px;
		left: 50%;
		margin-left: -45px;
		font-size: 25px;
		text-align: center;
		display: block;
	}
	.body-content-type-button .input .button{
		width: 80px;
		height: 35px;
		background: #000000;
		position: absolute;
		bottom: 0px;
		right: 0px;
		border-radius: 10px;
	}
	.body-content-type-button .input .button .show{
		width: calc(40px - 6px);
		height: calc(100% - 6px);
		position: absolute;
		top: 3px;
		left: 3px;
		background: #FFFFFF;
		border-radius: 10px;
		color: #000;
		font-size: 12px;
		text-align: center;
		line-height: 30px;
		transition: all 300ms ease;
		
	}
	
	.body-content-type-wenShiDu .output{
		width: 100px;
		height: 50px;
		/* border: 1px solid red; */
		display: block;
		text-align: left;
		position: absolute;
		bottom: 20px;
		left: 50%;
		margin-left: -50px;
	}
	
	.body-content-type-getBool .output{
		width: 80px;
		height: 50px;
		/* border: 1px solid red; */
		display: block;
		text-align: left;
		position: absolute;
		bottom: 20px;
		left: 50%;
		margin-left: -30px;
	}
	
	.body-content-type-leiDa .output{
		position: absolute;
		bottom: 0px;
		left: 50%;
		display: block;
		width: 150px;
		height: 90px;
		margin-left: -75px;
		/* border: 1px solid red; */
		
	}
	.body-content-type-leiDa .output > span{
		display: block;
		position: absolute;
		bottom: 0px;
		left: 50%;
		height: 100%;
		width: 4px;
		/* background: #42B983; */
		border-radius: 20px;
		transform-origin: bottom center;
		transform: rotate(30deg);
	}
	.body-content-type-leiDa .output > span > span{
		display: block;
		position: absolute;
		bottom: 0px;
		left:0px;
		height: 100%;
		width: 100%;
		background: #b90003;
		border-radius: 20px;
		transition: all 300ms ease;
	}
</style>
