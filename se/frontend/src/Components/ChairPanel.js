import React from 'react';
import {makeStyles} from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Link from '@material-ui/core/Link';
import Button from "@material-ui/core/Button";
import axios from "axios"

const useStyles = makeStyles((theme) => ({
    root: {
        flexGrow: 1,
    },
    menuButton: {
        marginRight: theme.spacing(2),
    },
    title: {
        flexGrow: 1,
    },
    bar: {
        justifyContent: "center",
    },
    item: {
        marginLeft: '15px',
        marginRight: '15px',
    }
}));

export default function ButtonAppBar() {
    const classes = useStyles();

    const tryGenerate = (event) => {
        event.preventDefault();
        if (window.confirm("Are you sure you want to generate the sections?")) {
            axios.defaults.baseURL = "http://localhost:8080";
            axios.get(`/conferences/generateSections`, {
                params: {
                    conferenceId: window.sessionStorage.getItem("conferenceId")
                }
            })
        }
    }

    return (
        <div className={classes.root}>
            <AppBar position="static">
                <Toolbar className={classes.bar}>
                    <Link href="/" color="inherit" className={classes.item}>Home</Link>
                    <Link href="/acceptedPapers" color="inherit" className={classes.item}>Accepted Papers</Link>
                    <Link href="/assignReviewer" color="inherit" className={classes.item}>Assign Reviewers</Link>
                    <Link href="/changeDeadline" color="inherit" className={classes.item}>Change Deadline</Link>
                    <Link href="/thirdPhaseDashboard" color="inherit" className={classes.item}>See sections</Link>
                    <Button color="inherit" onClick={tryGenerate}>
                        Generate sections
                    </Button>
                </Toolbar>
            </AppBar>
        </div>
    );
}
