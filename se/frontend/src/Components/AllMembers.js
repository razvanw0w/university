import React, {useEffect, useState} from 'react';
import Card from '@material-ui/core/Card';
import CardContent from '@material-ui/core/CardContent';
import CssBaseline from '@material-ui/core/CssBaseline';
import Grid from '@material-ui/core/Grid';
import Typography from '@material-ui/core/Typography';
import {makeStyles} from '@material-ui/core/styles';
import Container from '@material-ui/core/Container';
import Link from '@material-ui/core/Link';
import axios from 'axios';
import SteeringPanel from './SteeringPanel.js';
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

let cardsChairs = [];
let cardPcMembers = [];

export default function AllMembers() {
    const classes = useStyles();
    const [loading, setLoading] = useState(true);
    const [cardsChairs, setCardsChairs] = useState(null);
    const [cardsPcMembers, setCardsPcMembers] = useState(null);

   

    function AppBarSteering(){
        if(window.sessionStorage.getItem("userType")=="steering")
        {
            return <SteeringPanel></SteeringPanel>   
        }
        else
            return null;
    }

    function getAllChairs() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/chairs/getall/", {params: {
            conferenceId: window.sessionStorage.getItem("conferenceId")
        }});
    }

    function getAllPcMember() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/pcmembers/getall", {params: {
            conferenceId: window.sessionStorage.getItem("conferenceId")
        }});
    }

    async function get() {
        try {
            setLoading(true);
            const value = await getAllChairs();
            const value2 = await getAllPcMember();
            setCardsChairs(value.data);
            setCardsPcMembers(value2.data);
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
            <AppBarNavigation/>
            <CssBaseline/>
            <main>
                {/* Hero unit */}
                <div className={classes.heroContent}>
                    <Container maxWidth="sm">
                        <Typography variant="h5" align="center" color="textSecondary" paragraph>
                            All the Pc Members are: 
                        </Typography>
                    </Container>
                </div>
                <Container className={classes.cardGrid} maxWidth="md">
                    {/* End hero unit */}
                    <Grid container spacing={4}>
                        {cardsChairs.map((card) => (
                            <Grid item key={card.id} xs={12} sm={6} md={4}>
                                <Card className={classes.card}>
                                    <CardContent className={classes.cardContent}>
                                        <Typography gutterBottom variant="h5" component="h2">
                                            Chair: {card.name}
                                        </Typography>
                                    </CardContent>
                                </Card>
                            </Grid>
                        ))}
                        {cardsPcMembers.map((card) => (
                            <Grid item key={card.id} xs={12} sm={6} md={4}>
                                <Card className={classes.card}>
                                    <CardContent className={classes.cardContent}>
                                        <Typography gutterBottom variant="h5" component="h2">
                                            Pc Member: {card.name}
                                        </Typography>
                                    </CardContent>
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
