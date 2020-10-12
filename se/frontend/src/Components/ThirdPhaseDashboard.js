import React, {useEffect, useState} from 'react';
import Avatar from '@material-ui/core/Avatar';
import CssBaseline from '@material-ui/core/CssBaseline';
import Paper from '@material-ui/core/Paper';
import Grid from '@material-ui/core/Grid';
import WorkIcon from '@material-ui/icons/Assignment';
import {makeStyles} from '@material-ui/core/styles';
import axios from 'axios';
import ListItem from "@material-ui/core/ListItem";
import ListItemAvatar from "@material-ui/core/ListItemAvatar";
import ListItemText from "@material-ui/core/ListItemText";
import List from "@material-ui/core/List";
import AppBarNavigation from "./AppBarNavigation";
import Button from "@material-ui/core/Button";

const useStyles = makeStyles((theme) => ({
    root: {
        height: '100vh',
    },
    image: {
        backgroundImage: 'url(https://www.phonexia.com/en/wp-content/files/top-11-call-center-conferences-2020.jpg)',
        backgroundRepeat: 'no-repeat',
        backgroundColor:
            theme.palette.type === 'light' ? theme.palette.grey[50] : theme.palette.grey[900],
        backgroundSize: 'cover',
        backgroundPosition: 'center',
    },
    paper: {
        margin: theme.spacing(8, 4),
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
    },
    avatar: {
        margin: theme.spacing(1),
        backgroundColor: theme.palette.secondary.main,
    },
    form: {
        width: '50%', // Fix IE 11 issue.
        marginTop: theme.spacing(1),
    },
    submit: {
        margin: theme.spacing(3, 0, 2),
    },
}));

export default function CreateConferencePage() {
    const classes = useStyles();
    const [sections, setSections] = useState(null);
    const [loading, setLoading] = useState(true);
    const [isListener, setIsListener] = useState(false);
    const [feeValue, setFeeValue] = useState(null);

    function getAll() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get(`/conferences/${window.sessionStorage.getItem("conferenceId")}/planning`);
    }

    function addListener(sectionId) {
        if (window.confirm(`Are you sure you want to pay the fee?`)) {
            axios.defaults.baseURL = "http://localhost:8080";
            axios.post("/conferences/addListenerToSection", null, {
                params: {
                    conferenceId: sessionStorage.getItem("conferenceId"),
                    sectionId: sectionId,
                    userId: sessionStorage.getItem("userId")
                }
            }).then(r=>window.location.reload());
        }
    }

    function fee(){
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get(`/conferences/getFee/${window.sessionStorage.getItem("conferenceId")}`);
    }

    async function get() {
        try {
            setLoading(true);
            const val = await getAll();
            const getFee = await fee();
            setSections(val.data);
            setFeeValue(getFee.data);
        } catch (e) {
            console.log(e);
        } finally {
            setLoading(false);
        }
    }

    function PlanningList(props) {
        const sections = props.lst;
        const items = sections.map(section => (
            <ListItem>
                <ListItemAvatar>
                    <Avatar>
                        <WorkIcon/>
                    </Avatar>
                </ListItemAvatar>
                <ListItemText primary={`Conference: ${section.conferenceName} - Topic: ${section.sectionName}`}
                              secondary={`Room number: ${section.roomNumber} - Number of participants: ${section.noOfParticipants}`}/>
                {isListener ? (<Button onClick={() => addListener(section.sectionId)}>Pay Fee</Button>) : null}
            </ListItem>
        ));
        return (<List className={classes.root}>{items}</List>);
    }

    useEffect(() => {
        if (window.sessionStorage.getItem("userType") === "listener") {
            setIsListener(true);
        }
        get();
    }, []);

    return loading ? <p>"Loading..."</p> : (
        <Grid container component="main" className={classes.image}>
            <AppBarNavigation></AppBarNavigation>
            <CssBaseline/>
            <Grid item component={Paper} elevation={6} square className={classes.paperBack}>
                <div className={classes.paper}>
                    The fee for each section is: {feeValue}
                    <Grid className={classes.list}>
                        <PlanningList lst={sections}/>
                    </Grid>
                </div>
            </Grid>
        </Grid>
    );
}
