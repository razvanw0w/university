import React, {useEffect, useState} from 'react';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import CssBaseline from '@material-ui/core/CssBaseline';
import Grid from '@material-ui/core/Grid';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';
import Container from '@material-ui/core/Container';
import Link from '@material-ui/core/Link';
import axios from 'axios';
import AppBarNavigation from "./AppBarNavigation";
import Paper from "@material-ui/core/Paper";





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
        zIndex: '1'
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
    paperBack: {
        position: 'fixed',
        left: '25%',
        top: '10%',
        width: '50%',
        height : '80%',
        zIndex: '100',
        display: 'none',
        cursor: 'default',
        textAlign: 'center'
    },
    container: {
        margin: '0',
        width: '50%',
        position: 'relative',
        left: '25%',
        top: '10%',
    },

    item: {
        fontSize: '25px',
        margin: '1px',
        borderRadius: '5%',
        cursor: 'pointer',
        "&:hover": {
            backgroundColor: 'lightgray',
        }
    },

    closeButton: {
        position: 'absolute',
        bottom: '20px',
        fontSize: '20px',
        margin: '0 auto',
        width: '20%',
        left: '40%'
    }

}));

let cards = [];

export default function AssignReviewer() {
    const classes = useStyles();

    const [loading, setLoading] = useState(true);
    const [cards, setCards] = useState(null);
    const [loading2, setLoading2] = useState(true);
    const [cards2, setCards2] = useState(null);

    function getAll() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/proposals/getall",{params: {
            conferenceId: window.sessionStorage.getItem("conferenceId")
        }});
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

    function getAll2() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/pcmembers/getall",{params: {
            conferenceId: window.sessionStorage.getItem("conferenceId")
        }});
    }

    async function get2() {
        try {
            setLoading2(true);
            const value = await getAll2();
            setCards2(value.data);
        }
        catch (e) {
            console.log(e);
        }
        finally {
            setLoading2(false);
        }
    }

    useEffect(() => {
        get();
        get2();
    }, []);

    var selectedId = 0;

    function ShowReviewers(id) {
        selectedId = id;
        cards2.map(pc => pc.id).forEach(pc => document.getElementById(pc.toString()).style.textDecoration = 'none');
        cards2.map(pc => pc.id).forEach(pc => document.getElementById(pc.toString()).style.color = 'black');
        let refused = [];
        cards2.forEach(pc => {
           if(pc.refusedProposals.filter(proposal => proposal.id === id).length > 0) {
               refused.push(pc.id)
           }
           refused.forEach(pcid => document.getElementById(pcid.toString()).style.textDecoration = 'line-through');
        });
        let list = [];
        cards2.forEach(pc => {
            if(pc.reviewProposals.filter(proposal => proposal.id === id).length > 0) {
                list.push(pc.id)
            }
            list.forEach(pcid => document.getElementById(pcid.toString()).style.color = 'green');
        });
        document.getElementById('reviewers').style.display = 'block';
    }

    function CloseWindow(event) {
        event.preventDefault();
        document.getElementById('reviewers').style.display = 'none';
    }

    function SelectPC(id) {
        if(document.getElementById(id.toString()).style.textDecoration === 'line-through') {
            alert("This PC Member has refused to review this proposal!");
        }
        else if(document.getElementById(id.toString()).style.color === 'green') {
            alert("This PC Member has already been assigned to review this proposal!")
        }
        else {
            axios.defaults.baseURL = "http://localhost:8080";
            axios.post('/proposals/assignReviewer/' + selectedId + "/" + id, null, {
                params: {}
            })
                .then(response => {
                    console.log(response);
                    document.getElementById(id.toString()).style.color = 'green';
                })
                .catch(error => console.log(error));
        }
    }


    return loading || loading2 ? <p>"stillloading"</p>: (
        <React.Fragment>
            <AppBarNavigation></AppBarNavigation>
            <CssBaseline />
            <main>

                {/* Hero unit */}
                <div className={classes.heroContent}>
                    <Container maxWidth="sm">
                        {/*<Typography component="h1" variant="h2" align="center" color="textPrimary" gutterBottom>*/}
                        {/*    Final results*/}
                        {/*</Typography>*/}
                        <Typography variant="h5" align="center" color="textSecondary" paragraph>
                            Assign reviewers
                        </Typography>
                    </Container>
                </div>

                <Grid item component={Paper} elevation={6} square className={classes.paperBack} id="reviewers">
                    <div className={classes.container}>
                        {cards2.map(card => (
                            <div key={card.id} id={card.id} className={classes.item} onClick={() => SelectPC(card.id)}>{card.name}</div>
                        ))}
                    </div>
                    <Button className={classes.closeButton} onClick={CloseWindow}>
                        CLOSE
                    </Button>
                </Grid>

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
                                    <CardActions>
                                        <Button size="small" color="primary" className={classes.btn} onClick={() => ShowReviewers(card.id)}>
                                            Assign Reviewer
                                        </Button>
                                    </CardActions>
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
