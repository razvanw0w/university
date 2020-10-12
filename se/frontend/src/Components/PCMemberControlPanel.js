import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import Button from '@material-ui/core/Button';
import IconButton from '@material-ui/core/IconButton';
import MenuIcon from '@material-ui/icons/Menu';
import Link from "@material-ui/core/Link";
import {cadetblue, white} from "color-name";
import {red} from "@material-ui/core/colors";

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
export default function PCMemberControlPanel(){
    const classes = useStyles();

    return (
        <div className={classes.root}>
            <div className={classes.root}>
                <AppBar position="static">
                    <Toolbar className={classes.bar}>
                        <Link href="/" color="inherit" className={classes.item}>Home</Link>
                        <Link href="/bidding" color="inherit" className={classes.item}>Bidding</Link>
                        <Link href="/review" color="inherit" className={classes.item}>Review</Link>
                        <Link href="/seeFinalResults" color="inherit" className={classes.item}>Show final results</Link>
                        <Link href="/thirdPhaseDashboard" color="inherit" className={classes.item}>See sections</Link>
                    </Toolbar>
                </AppBar>
            </div>
        </div>
    );
}
