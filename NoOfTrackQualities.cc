#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// because i want to use tracks data type
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
//

#include "FWCore/MessageLogger/interface/MessageLogger.h"



#include "TH1.h"

//
// class declaration
//

class trackparam : public edm::EDAnalyzer {
   public:
      explicit trackparam(const edm::ParameterSet&);
      ~trackparam();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
    int loose, tight, highpurity;
};

//
// constants, enums and typedefs
//
//
//
// static data member definitions
//

//
// constructors and destructor
//
trackparam::trackparam(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

 

}


trackparam::~trackparam()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
trackparam::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
// aim // we want to print 5 tracks paramters in every event

   using namespace edm;
using namespace std;

   Handle<vector<reco::Track>> tracks;
   iEvent.getByLabel("generalTracks", tracks); 
  for (reco::TrackCollection::const_iterator track = tracks->begin();  track != tracks->end();  ++track) {
j = j+1;

if (track -> quality(reco::Track::qualityByName("loose")))
noloose += 1;

if (track -> quality(reco::Track::qualityByName("tight")))
notight += 1;

if (track -> quality(reco::Track::qualityByName("highPurity")))
nohighPurity += 1;


}
 cout << "noloose = "<<noloose << endl;
 cout << "notight = "<<notight << endl;
 cout << "nohighPurity"<<nohighPurity << endl;
cout <<"no. of tracks equal" << j <<endl;


   

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
trackparam::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
trackparam::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
trackparam::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
trackparam::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
trackparam::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
trackparam::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
trackparam::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(trackparam);
