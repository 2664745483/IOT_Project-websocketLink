package com.hwl.websocket.mode;

public class MessageData {
    private String to = "";
    private String type = "";
    private String value = "";

    public MessageData() {
    }

    public MessageData(String to, String value) {
        this.to = to;
        this.value = value;
    }


    @Override
    public String toString() {
        return "MessageData{" +
                "to='" + to + '\'' +
                ", type='" + type + '\'' +
                ", value='" + value + '\'' +
                '}';
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
}
