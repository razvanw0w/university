import React from "react";
import PCMemberControlPanel from "./PCMemberControlPanel";
import ChairPanel from "./ChairPanel";
import SteeringPanel from "./SteeringPanel"
import AuthorPanel from "./AuthorPanel";
import UserPanel from "./UserPanel";
import ListenerPanel from "./ListenerPanel";

export default function AppBarNavigation() {
    if (window.sessionStorage.getItem('userType') == 'pcmember') {
        return <PCMemberControlPanel></PCMemberControlPanel>
    } else if (window.sessionStorage.getItem('userType') == 'chair') {
        return <ChairPanel></ChairPanel>
    } else if (window.sessionStorage.getItem('userType') == 'author') {
        return <AuthorPanel></AuthorPanel>;
    }
    else if(window.sessionStorage.getItem('userType') == 'steering'){
        return <SteeringPanel></SteeringPanel>;
    }
    else if(window.sessionStorage.getItem('userType') == 'listener'){
        return <ListenerPanel></ListenerPanel>;
    }
    else {
        return <UserPanel></UserPanel>;
    }
}
