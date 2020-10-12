import React, {useState} from 'react';
import Avatar from '@material-ui/core/Avatar';
import Button from '@material-ui/core/Button';
import CssBaseline from '@material-ui/core/CssBaseline';
import Link from '@material-ui/core/Link';
import Box from '@material-ui/core/Box';
import AttachmentIcon from '@material-ui/icons/Attachment';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';
import Container from "@material-ui/core/Container";
import axios from "axios";
import AppBarNavigation from "./AppBarNavigation";
import Grid from "@material-ui/core/Grid";



const useStyles = makeStyles((theme) => ({
    root: {
        height: '100vh',
    },
    image: {
        backgroundImage: 'url(https://source.unsplash.com/random)',
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
        margin: theme.spacing(4),
        backgroundColor: theme.palette.secondary.main,
    },
    form: {
        width: '100%', // Fix IE 11 issue.
        marginTop: theme.spacing(1),
    },
    submit: {
        margin: theme.spacing(3, 0, 2),
    },
}));

export default function SubmitProposal() {

    const fileRef = React.createRef();

    function uploadFileToServer(e){
        e.preventDefault();
        console.log("atata merge");
        const formData = new FormData();
        let userId = window.sessionStorage.getItem("userId")
        var fileInput  = document.querySelector('input[type=file]').files[0];
        console.log(fileInput);
        formData.set('file', fileInput, fileInput.name);
        formData.set('userId',userId);
        formData.set('fileCategory', 'paper');
        console.log(formData);
        axios.defaults.baseURL = "http://localhost:8080";

        axios({
            method: 'post',
            url: '/proposals/upload/',
            data: formData,
            headers: {'Content-Type': 'multipart/form-data' }
        })
            .then(function (response) {
                //handle success
                console.log(response);
                window.alert("proposal added!")
            })
            .catch(function (response) {
                //handle error
                console.log(response);
            });
    }

    const classes = useStyles();
    return (
        <Container component="main" maxWidth="xs">
            <AppBarNavigation></AppBarNavigation>
            <br/>
            <CssBaseline />
            <div className={classes.paper}>
                <Typography component="h1" variant="h5">
                    Submit your proposal here!
                </Typography>

                <Avatar className={classes.avatar}>
                    <AttachmentIcon/>
                </Avatar>

                <Button
                    fullWidth
                    variant="contained"
                    color="primary"
                    className={classes.submit} >
                    <input className={classes.input} id="icon-button-file" type="file" ref={fileRef} />
                </Button>
                <Button
                    type="submit"
                    onClick={uploadFileToServer}
                    fullWidth
                    variant="contained"
                    color="primary"
                    className={classes.submit}
                >
                    Upload file
                </Button>
            </div>
            
        </Container>
    );

}
