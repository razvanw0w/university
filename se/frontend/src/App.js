import React from 'react';
import {Route, Switch} from 'react-router-dom';
import './App.css';

import SeeFinalResults from "./Components/SeeFinalResults";
import SignUpPage from "./Components/SignUpPage";
import LogInPage from "./Components/LogInPage";
import SubmitMetaInfo from "./Components/SubmitMetaInfo";
import SubmitProposal from "./Components/SubmitProposal";
import ConferenceCreation from "./Components/ConferenceCreation";
import AcceptedPaperPage from "./Components/AcceptedPaperPage";
import ShowReviewedProposals from "./Components/ShowReviewedProposals";
import AssignReviewer from "./Components/AssignReviewer";
import BiddindPCMember from "./Components/BiddindPCMember";
import ReviewPCMember from "./Components/ReviewPCMember";
import PCMemberControlPanel from "./Components/PCMemberControlPanel";
import ThirdPhaseDashboard from "./Components/ThirdPhaseDashboard";
import AllMembers from './Components/AllMembers';
import AuthorPanel from "./Components/AuthorPanel";

import homePage from "./Components/HomePage"
import ChangeDeadline from "./Components/ChangeDeadline";
import ShowAuthorsProposal from "./Components/ShowAuthorsProposal";


function App() {
  return (
      <main>
          <Switch>
              <Route path="/showAuthorsProposal" component={ShowAuthorsProposal}/>
              <Route path="/pcmemberControlPanel" component={PCMemberControlPanel}/>
              <Route path="/thirdPhaseDashboard" component={ThirdPhaseDashboard}/>
              <Route path="/authorPanel" component={AuthorPanel}/>
              <Route path="/showReviewedProposals" component={ShowReviewedProposals}/>
              <Route path="/assignReviewer" component={AssignReviewer} />
              <Route path="/seeFinalResults" component={SeeFinalResults} />
              <Route path="/acceptedPapers" component={AcceptedPaperPage} />
              <Route path="/changeDeadline" component={ChangeDeadline} />
              <Route path="/conferenceCreation" component={ConferenceCreation} />
              <Route path="/submitMetaInfo" component={SubmitMetaInfo} />
              <Route path="/bidding" component={BiddindPCMember} />
              <Route path="/review" component={ReviewPCMember} />
              <Route path="/submitProposal" component={SubmitProposal} />
              <Route path="/signUp" component={SignUpPage} exact />
              <Route path="/logIn" component={LogInPage}/>
              <Route path="/allmembers" component={AllMembers}/>
              <Route path="/" component={homePage}/>
          </Switch>
      </main>
  );
}

export default App;
