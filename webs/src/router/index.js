import Vue from 'vue'
import Router from 'vue-router'
// import Echarts from 'echarts'
// import HelloWorld from '@/components/HelloWorld'
import Main		from '@/pages/main.vue'



Vue.use(Router)
// Vue.use(Echarts)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Main',
      component: Main
    }
  ]
})
