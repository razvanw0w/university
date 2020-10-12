package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.junit.Before;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.ResultActions;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Proposal;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.AuthorRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.PCMemberRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.ProposalRepository;

import java.util.Arrays;
import java.util.List;

import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.Matchers.is;
import static org.mockito.Mockito.when;
import static org.mockito.MockitoAnnotations.initMocks;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

public class ProposalControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private ProposalController proposalController;

    @Mock
    private ProposalRepository proposalRepository;

    @Mock
    private PCMemberRepository pcMemberRepository;

    @Mock
    private AuthorRepository authorRepository;

    private Proposal proposal1;
    private Proposal proposal2;

    @Before
    public void setup() throws Exception {
        initMocks(this);
        this.mockMvc = MockMvcBuilders.standaloneSetup(proposalController).build();
        initData();
    }

    @Test
    public void getAllProposals() throws Exception {
        List<Proposal> proposals = Arrays.asList(proposal1, proposal2);
        when(proposalRepository.findAll()).thenReturn(proposals);

        ResultActions resultActions = mockMvc.perform(MockMvcRequestBuilders.get("/proposals/all"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].id", is(1)))
                .andExpect(jsonPath("$[0].title", is("t1")))
                .andExpect(jsonPath("$[0].authors", is("a1,b1,c1")))
                .andExpect(jsonPath("$[0].paperFile", is("pf1")))
                .andExpect(jsonPath("$[0].abstractFile", is("af1")))
                .andExpect(jsonPath("$[1].id", is(2)))
                .andExpect(jsonPath("$[1].title", is("t2")))
                .andExpect(jsonPath("$[1].authors", is("a2,b2,c2")))
                .andExpect(jsonPath("$[1].paperFile", is("pf2")))
                .andExpect(jsonPath("$[1].abstractFile", is("af2")));
    }

    private void initData() {
        proposal1 = new Proposal();
        proposal1.setId(1);
        proposal1.setTitle("t1");
        proposal1.setAuthors("a1,b1,c1");
        proposal1.setPaperFile("pf1");
        proposal1.setAbstractFile("af1");
        proposal1.setStatus("s1");
        proposal2 = new Proposal();
        proposal2.setId(2);
        proposal2.setTitle("t2");
        proposal2.setAuthors("a2,b2,c2");
        proposal2.setPaperFile("pf2");
        proposal2.setAbstractFile("af2");
        proposal2.setStatus("s2");
    }
}
