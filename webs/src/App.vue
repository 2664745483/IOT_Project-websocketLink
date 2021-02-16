<template>
  <div id="app">
    <!-- <img src="./assets/logo.png"> -->
    <router-view/>
	<Tab-Component></Tab-Component>
  </div>
</template>

<script>
import Tab_Component	from '@/components/Tab_Component.vue'
	
export default {
  name: 'App',
  components:{
	  "Tab-Component":Tab_Component
  }
}
</script>
<style>
html,body,#app{
	width:100%;
	height:100%;
	position:absolute;
	top:0px;
	left:0px;
	overflow:auto;
}
*{
	margin:0px;
	padding:0px;
}
li{
	list-style: none;
}
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #FFF;
  margin-top: 0px;
}
	
</style>
