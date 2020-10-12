import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Link from '@material-ui/core/Link';

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

export default function SteeringPanel() {
    const classes = useStyles();

    return (
        <div className={classes.root}>
            <AppBar position="static">
                <Toolbar className={classes.bar}>
                    <Link href="/" color="inherit" className={classes.item}>Home</Link>
                    <Link href="/conferenceCreation" color="inherit" className={classes.item}>Create Conference</Link>
                    <Link href="/allmembers" color="inherit" className={classes.item}>See PC Members</Link>
                    <Link href="/thirdPhaseDashboard" color="inherit" className={classes.item}>See sections</Link>
                </Toolbar>
            </AppBar>
        </div>
    );
}