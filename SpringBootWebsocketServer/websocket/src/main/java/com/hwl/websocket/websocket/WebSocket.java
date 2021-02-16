package com.hwl.websocket.websocket;


import com.alibaba.fastjson.JSON;
import com.hwl.websocket.mode.MessageData;
import org.springframework.stereotype.Component;

import javax.websocket.*;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;


/**
 * @Auther: shigc
 * iot_id 是iot_的标识
 * @Date: 2018/12/15 11:53
 * @Description: websocket
 */
@ServerEndpoint("/websocket/{iot_id}")
@Component
public class WebSocket {



    private static final String loggerName=WebSocket.class.getName();
    //concurrent包的线程安全Set，用来存放每个客户端对应的MyWebSocket对象。若要实现服务端与单一客户端通信的话，可以使用Map来存放，其中Key可以为用户标识
    public static Map<String, List<Session>> electricSocketMap = new ConcurrentHashMap<String, List<Session>>();

    /**
     * 连接建立成功调用的方法
     *
     * @param session 可选的参数。session为与某个客户端的连接会话，需要通过它来给客户端发送数据
     */
    @OnOpen
    public void onOpen(@PathParam("iot_id") String iot_id, Session session) {

        List<Session> sessions = electricSocketMap.get(iot_id);
        if(null==sessions){
            //增加新用户
            System.out.println("没有用户添加用户 id:"+iot_id+" sessionID"+session.getId());
            List<Session> sessionList = new ArrayList<>();
            sessionList.add(session);
            electricSocketMap.put(iot_id,sessionList);

        }else{
            System.out.println("已有用户添加session id:"+iot_id+" sessionID"+session.getId());
            sessions.add(session);
        }
    }

    /**
     * 连接关闭调用的方法
     */
    @OnClose
    public void onClose(@PathParam("iot_id") String pageCode,Session session) {
        if (electricSocketMap.containsKey(pageCode)){
            electricSocketMap.get(pageCode).remove(session);
        }
    }

    /**
     * 收到客户端消息后调用的方法
     *
     * @param message 客户端发送过来的消息
     * @param session 可选的参数
     */
    @OnMessage
    public void onMessage(String message, Session session) {
//        System.out.println("websocket received message:"+message);
        try {
//            System.out.println("发送给自己的数据:"+message);
            session.getBasicRemote().sendText(message);
        } catch (IOException e) {
            e.printStackTrace();
        }
        //给别人发送数据
        MessageData messageData = JSON.parseObject(message, MessageData.class);


        List<Session> sessions = electricSocketMap.get(messageData.getTo());

        for ( Session session1: sessions) {
            try {
                session1.getBasicRemote().sendText(message);
            } catch (IOException e) {
            }
        }


    }

    /**
     * 发生错误时调用
     *
     * @param session
     * @param error
     */
    @OnError
    public void onError(Session session, Throwable error) {
        System.out.println("发生错误 sessionID : "+session.getId());;
    }


}