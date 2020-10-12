import React, {useEffect, useState} from 'react';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import CssBaseline from '@material-ui/core/CssBaseline';
import Grid from '@material-ui/core/Grid';
import Typography from '@material-ui/core/Typography';
import {makeStyles} from '@material-ui/core/styles';
import Container from '@material-ui/core/Container';
import Link from '@material-ui/core/Link';
import axios from 'axios';
import AppBarNavigation from "./AppBarNavigation";




const useStyles = makeStyles((theme) => ({
    icon: {
        marginRight: theme.spacing(2),
    },
    heroContent: {
        backgroundColor: theme.palette.background.paper,
        padding: theme.spacing(8, 0, 6),
    },
    heroButtons: {
        marginTop: theme.spacing(4),
    },
    cardGrid: {
        paddingTop: theme.spacing(8),
        paddingBottom: theme.spacing(8),
    },
    card: {
        height: '100%',
        display: 'flex',
        flexDirection: 'column',
    },
    cardMedia: {
        paddingTop: '56.25%', // 16:9
    },
    cardContent: {
        flexGrow: 1,
    },
    footer: {
        backgroundColor: theme.palette.background.paper,
        padding: theme.spacing(6),
    },
}));

let cards = [];

export default function SeeFinalResults() {
    const classes = useStyles();
    const [loading, setLoading] = useState(true);
    const [cards, setCards] = useState(null);

    function getAll() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/proposals/getall",{params: {
            conferenceId: window.sessionStorage.getItem("conferenceId")
        }});
    }

    function sendMailToAuthor(){
        var variables = {email: 'ungureanu.vlad1@gmail.com'};

        window.emailjs.send(
            'gmail',
            'succesfully_registered',
            variables
        ).then(res => {
            console.log('Email successfully sent!')
        })
            // Handle errors here however you like, or use a React error boundary
            .catch(err => console.error('Oh well, you failed. Here some thoughts on the error that occured:', err))
    }

    async function get() {
        try {
            setLoading(true);
            const value = await getAll();
            setCards(value.data);
        }
        catch (e) {
            console.log(e);
        }
        finally {
            setLoading(false);
        }
    }

    useEffect(() => {
        get();
    }, []);

    return loading ? <p>"stillloading"</p>: (
        <React.Fragment>
            <AppBarNavigation></AppBarNavigation>
            <CssBaseline/>
            <main>
                {/* Hero unit */}
                <div className={classes.heroContent}>
                    <Container maxWidth="sm">
                        {/*<Typography component="h1" variant="h2" align="center" color="textPrimary" gutterBottom>*/}
                        {/*    Final results*/}
                        {/*</Typography>*/}
                        <Typography variant="h5" align="center" color="textSecondary" paragraph>
                            Final results for each paper.
                        </Typography>
                    </Container>
                </div>
                <Container className={classes.cardGrid} maxWidth="md">
                    {/* End hero unit */}
                    <Grid container spacing={4}>
                        {cards.map((card) => (
                            <Grid item key={card.id} xs={12} sm={6} md={4}>
                                <Card className={classes.card}>
                                    <CardContent className={classes.cardContent}>
                                        <Typography gutterBottom variant="h5" component="h2">
                                            {card.title}
                                        </Typography>
                                        <Typography>
                                            Authors: {card.authors}
                                        </Typography>
                                        <Typography>
                                            Status: {card.status}
                                        </Typography>
                                    </CardContent>
                                    {/*<CardActions>*/}
                                    {/*    <Button size="small" color="primary">*/}
                                    {/*        Send email*/}
                                    {/*    </Button>*/}
                                    {/*</CardActions>*/}
                                </Card>
                            </Grid>
                        ))}
                    </Grid>
                </Container>
            </main>
            {/* Footer */}
            <footer className={classes.footer}>
                <Typography variant="h6" align="center" gutterBottom>
                    Footer
                </Typography>
                <Typography variant="subtitle1" align="center" color="textSecondary" component="p">
                    Something here to give the footer a purpose!
                </Typography>
               
            </footer>
            {/* End footer */}
        </React.Fragment>
    );
}
